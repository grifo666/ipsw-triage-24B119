# restartWithDyldInCache

- Simbolo: `__ZN5dyld422restartWithDyldInCacheEPKNS_10KernelArgsEPKN6mach_o12UnsafeHeaderEPK15DyldSharedCacheyPv.c` (15 linhas), Ghidra headless
- Classificacao: **stub de salto indireto; corpo nao recuperado**

## Comportamento

```
(*param_5)();
return;
```

Chama um ponteiro de funcao recebido como 5o argumento (`param_5`). Os demais argumentos (KernelArgs, UnsafeHeader, DyldSharedCache, endereco de entrada) sao repassados pela convencao de chamada para o destino.

## Observacao

O Ghidra nao recuperou o destino ("Could not recover jumptable... Too many branches; Treating indirect jump as call"). E um trampolim para reiniciar a execucao a partir do dyld do cache (restart). O corpo real depende do ponteiro, provavelmente o ponto de entrada do novo dyld em `param_5`. Sem logica propria visivel para auditar aqui; nao ha alocacao nem escrita.

## Classificacao final

- Sem defeito no nivel deste stub. Depende do destino em `param_5`.

