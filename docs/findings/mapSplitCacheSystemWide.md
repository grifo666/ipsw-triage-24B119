# mapSplitCacheSystemWide

- Simbolo: `__ZN5dyld3L23mapSplitCacheSystemWideERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoE.c`
- Build: iOS 27.2 (24B119), base 26.6.1 (23G83), alvo iPhone18,2
- Fonte: `06-decomp/dyld/__ZN5dyld3L23mapSplitCacheSystemWide...c` (525 linhas), Ghidra headless
- Classificacao: **bug real de vazamento de file descriptors nos caminhos de falha**

## Contexto

Sequencia: `preflightMainCacheFile` (linha 327) abre o cache principal e preenche o `CacheInfo` em `aCStack_e978`; se ok, um loop (338-360) chama `preflightSubCacheFile` para cada subcache, abrindo mais fds. So depois, no caminho de sucesso, vem `DynamicRegion::make`, o preenchimento da tabela de mappings, o syscall `___shared_region_map_and_slide_2_np` (471) e, por fim, o **unico** loop de `_close` (473-482).

## Defeito - fds vazam nos dois caminhos de falha

O loop de `_close` esta exclusivamente no caminho feliz, depois do syscall:

```
473:      if (local_e7d0 != 0) {
475:        do {
476:          if (local_e000[lVar14 * 0x70 + 2] != 0xffffffff) {
477:            _close(local_e000[lVar14 * 0x70 + 2]);
```

Os dois `goto LAB_180509c60` que pulam esse loop:

1. Falha de preflight de subcache:
```
353:        if ((uVar11 & 1) == 0) {
354:          uVar10 = 0;
355:          goto LAB_180509c60;      // nenhum _close: vaza main + subcaches ja abertos
```

2. Falha de `DynamicRegion::make` (linha 362, `this == 0`): seta "Could not vm_allocate dynamic config memory", `uVar10 = 0`, e cai ate LAB_180509c60 sem fechar nada.

Em ambos, o fd do cache principal (em `aCStack_e978`) e todos os fds de subcache ja abertos em `local_e180` ficam abertos. `preflightMainCacheFile` e `preflightSubCacheFile` fazem `openat` e transferem o fd no `CacheInfo`; a funcao chamadora e a unica responsavel por fecha-los, e so fecha no sucesso.

## Impacto

Vazamento de fd por tentativa que falha. Nao e corrupcao de memoria, e robustez: num processo que re-tenta mapear caches (ou em falha repetida de subcache), o consumo de fds cresce ate esgotar a tabela e derrubar `openat` de qualquer outra coisa. O padrao correto e um bloco de limpeza unico alcancado por todos os exits, como o `goto` deveria pular para um epilogo que fecha os fds antes de retornar.

## Observacao secundaria

`preflightMainCacheFile` e chamado com `param_6 = NULL` (linha 327) e `preflightSubCacheFile` recebe `pSVar13` (o `SharedCacheLoadInfo`) no 6o argumento (linha 352). Em `preflightCacheFile` o 6o argumento so serve para herdar o byte `+0x19` quando nao-NULL (linhas 179-181). Ou seja, o subcache herda a flag de validacao do main por passthrough, coerente com o ja registrado no AGENTS.md; nao e defeito, apenas confirma o desenho.

## Classificacao final

- Vazamento de fd nos caminhos de falha (preflight de subcache e `DynamicRegion::make`): bug real, exploravel como esgotamento de recurso sob falha repetida.
