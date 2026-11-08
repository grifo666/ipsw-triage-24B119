# preflightMainCacheFile

- Simbolo: `__ZN5dyld3L22preflightMainCacheFileERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoEPNS_9CacheInfoEPcPNSt3__15arrayIA32_cLm128EEE.c` (90 linhas), Ghidra headless
- Classificacao: **dono do fd principal; sem defeito proprio, mas origem do fd vazado**

## Comportamento

Itera sobre a tabela de nomes de arquitetura (`archNames`, passos de 0x10, ate 0x10 entradas) montando o nome `dyld_shared_cache_<arch>`. Se a opcao de desenvolvimento nao estiver setada (`SVar1 & 1 == 0`), tenta a variante `.development` e aplica a logica de override por `/System/Library/Caches/com.apple.dyld/enable-dylibs-to-override-cache` (se existir e tiver `st_size < 0x400`, mantem `.development`). Abre com `openat` e, no primeiro que abrir, chama `preflightCacheFile`.

```
do {
  ... monta local_270 ...
  iVar6 = openat(*(int*)param_1, local_270);
  lVar10 += 0x10; bVar4 = lVar11 != 0; lVar11 -= 0x10;
} while (iVar6 == -1 && bVar4);
if (iVar6 == -1) { ... "no shared cache file" / "open() failed" ... }
else { param_2[0x18] = 1; preflightCacheFile(param_1,param_2,param_3,iVar6,param_5,NULL); }
```

## Observacao

O 6o argumento passado a `preflightCacheFile` e `NULL` (o LoadInfo principal, ja que este e o cache principal). O fd aberto sai da funcao sem `_close` e e de responsabilidade dos chamadores, exatamente como em `preflightSubCacheFile`. O loop e limitado a 0x10 entradas e o nome e truncado a 0x100 por `strlcpy`/`strlcat`, sem overflow. A logica `.development` so roda com a opcao desligada e nunca com stat de tamanho invalido (guarda `st_size < 0x400`).

Nao ha defeito proprio. O fd principal que esta funcao abre e o primeiro a vazar quando um preflight de subcache falha nos mappers.

## Classificacao final

- Sem defeito proprio. Abre o fd principal e o repassa; nao fecha, alimentando o vazamento no caminho de erro dos chamadores.
