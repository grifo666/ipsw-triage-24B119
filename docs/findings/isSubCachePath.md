# isSubCachePath

- Simbolo: `__ZN15DyldSharedCache14isSubCachePathEPKc.c` (20 linhas), Ghidra headless
- Classificacao: **heuristica simples; sem bug de memoria**

## Comportamento

```
pcVar2 = strchr(param_1, '.');
if (pcVar2 == NULL || strcmp(pcVar2, ".development") == 0)
    return 0;      // nao e subcache
return 1;          // tem sufixo de subcache
```

## Logica

A funcao classifica um nome de arquivo: se nao ha ponto, ou se o unico ponto inicia o sufixo `.development`, trata como cache principal; qualquer outro sufixo com ponto e considerado subcache (`.1`, `.2`, `.symbols`, etc).

## Observacao

`strchr` acha o **primeiro** ponto, e `strcmp(pcVar2, ".development")` exige que o restante seja exatamente `.development`. Um nome como `dyld_shared_cache_arm64e.1.development` teria o primeiro ponto em `.1.development`, cujo `strcmp` falha, logo retorna 1 (subcache) — o que e correto. Um arquivo chamado `foo.development` (sem cache base) tambem vira "nao subcache", coerente. Nao ha escrita, so leitura; sem risco.

## Classificacao final

- Sem defeito. Heuristica de nome, so leitura.
