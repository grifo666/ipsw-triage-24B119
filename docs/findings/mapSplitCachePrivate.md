# mapSplitCachePrivate

- Simbolo: `__ZN5dyld3L20mapSplitCachePrivateERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoE.c` (951 linhas), Ghidra headless
- Build: iOS 27.2 (24B119), base 26.6.1 (23G83), alvo iPhone18,2
- Classificacao: **bug real de vazamento de fd no caminho de falha de subcache**

## Contexto

Versao "privada ao processo" do mapeamento: `preflightMainCacheFile` (376) abre o cache principal, um loop chama `preflightSubCacheFile` para cada subcache (408), depois vem `deallocateExistingSharedCache`, o `mmap` de cada regiao (451), `DynamicRegion::make` (487) e, no fim, o loop de `_close` (928-938).

## Defeito - fd vaza quando o preflight de subcache falha

O caminho de falha do subcache:
```
412:        if ((int)uVar12 == 0) goto LAB_180508a30;
...
947:LAB_180508a30:
948:  bVar20 = 0;
949:  goto LAB_1805095f4;      // retorna sem _close
```

`LAB_1805095f4` so confere o stack canary e retorna. Ou seja: o fd do cache principal (aberto por `preflightMainCacheFile` em 376) e todos os fds de subcache ja abertos ficam abertos ao sair por aqui.

Ha dois loops de `_close` e nenhum cobre este caminho:
- 462-471: so no erro de `mmap` de regiao (fecha e depois `goto LAB_180508a30`, reusando o mesmo rotulo de saida — mas ja fechou antes de pular).
- 928-938: so no caminho de sucesso, apos todo o processamento.

O `goto LAB_180508a30` da linha 412 pula direto para a saida comum, sem passar por nenhum dos dois. Diferente do caminho de erro de `mmap` (que fecha explicitamente antes de ir ao rotulo), o erro de preflight de subcache nao fecha nada.

## Impacto

Mesmo defeito de `mapSplitCacheSystemWide`: vazamento de fd por tentativa que falha no preflight de um subcache. Como este e o caminho privado (o que roda quando `loadDyldCache` ve `param_1[4] == 1`), e atingivel sob demanda. Repeticao esgota a tabela de fds.

## Classificacao final

- Vazamento de fd no caminho de falha de `preflightSubCacheFile`: bug real, mesmo padrao do systemwide. A correcao natural e o rotulo de saida fechar os fds ja abertos antes de retornar.
