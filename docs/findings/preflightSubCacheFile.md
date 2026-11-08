# preflightSubCacheFile

- Simbolo: `__ZN5dyld3L21preflightSubCacheFileERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoEPNS_9CacheInfoEPcPKcPKS3_.c` (44 linhas), Ghidra headless
- Classificacao: **dono do fd do subcache; nao o fecha, alimenta o vazamento dos mappers**

## Comportamento

Monta o caminho concatenando `param_4` (diretorio/base) com `param_5` (nome) via `strlcpy`+`strlcat` em buffer de 0x100, abre com `openat(dirfd, caminho)` e, se abrir, chama `preflightCacheFile`.

```
strlcpy(acStack_158, param_4, 0x100);
strlcat(acStack_158, param_5, 0x100);
iVar1 = openat(*(int*)param_1, acStack_158);
if (iVar1 == -1) { ... erro "no shared cache file" / "open() failed" ... }
else {
  param_2[0x18] = 1;
  uVar2 = preflightCacheFile(param_1, param_2, param_3, iVar1, NULL, param_6);
}
```

O fd aberto (`iVar1`) e passado a `preflightCacheFile` e **nao e fechado aqui**; quem fecha sao os chamadores (`mapSplitCacheSystemWide`/`mapSplitCachePrivate`), no fim ou no erro de mmap.

## Observacao - ligacao com o vazamento

Como o fd sai aberto da funcao, ele depende inteiramente dos loops de `_close` dos mappers. No caminho de falha de preflight de um subcache subsequente, esses loops nao rodam (ver mapSplitCacheSystemWide.md / mapSplitCachePrivate.md) e o fd deste subcache ja aberto vaza junto com o do cache principal. Aqui nao ha defeito proprio, mas e a origem dos fds que os mappers vazam.

Detalhe: `param_2` e um `SharedCacheLoadInfo` local do chamador por subcache, nao o principal; `param_6` (o LoadInfo principal) e passthrough puro repassado como 6o argumento a `preflightCacheFile`.

## Classificacao final

- Sem defeito proprio. Abre o fd e o entrega adiante; a responsabilidade de fechar e dos chamadores, que falham no caminho de erro de subcache.

