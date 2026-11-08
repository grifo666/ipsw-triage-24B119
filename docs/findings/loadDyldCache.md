# loadDyldCache

- Simbolo: `__ZN5dyld313loadDyldCacheERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoE.c` (36 linhas), Ghidra headless
- Classificacao: **dispatcher; sem defeito proprio**

## Comportamento

Zera tres palavras de `param_2` (o `SharedCacheLoadInfo`) e despacha:

```
if (param_1[4] == 1) {                // modo privado
    SoftwareBreakpoint(0xc471) se ... // sanity
    return mapSplitCachePrivate(param_1,param_2);
}
iVar2 = reuseExistingCache(param_1,param_2);
if (iVar2 != 0) return (*(long *)(param_2 + 0x10) == 0);
SoftwareBreakpoint(0xc471) se ...
return mapSplitCacheSystemWide(param_1,param_2);
```

- `param_1[4]` seleciona privado vs system-wide.
- No caminho system-wide, tenta `reuseExistingCache` primeiro; se reaproveitou, retorna se nao ha erro (offset 0x10 do LoadInfo == 0).
- Senao, delega a `mapSplitCacheSystemWide`.

## Observacao

As guardas `SoftwareBreakpoint(0xc471)` sao traps de consistencia (`x30` comparado consigo mesmo, um truque de `PAC`/assinatura que o decompilador nao resolve). Nao ha alocacao nem escrita alem do zero inicial de 24 bytes. A zeragem dos tres qwords cobre exatamente o inicio do `SharedCacheLoadInfo`, deixando os mapas limpos antes do dispatch. A logica de decisao e curta e correta.

## Classificacao final

- Sem defeito. Apenas despacho e zeragem inicial; os defeitos vivem nos callees (`mapSplitCacheSystemWide`, `mapSplitCachePrivate`).
