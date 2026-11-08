# setRootsBitmaps

- Simbolo: `__ZN15DyldSharedCache13DynamicRegion15setRootsBitmapsEjNSt3__14spanIKhLm18446744073709551615EEES4_h.c` (58 linhas), Ghidra headless
- Classificacao: **robusto; guardas de overflow e limite de buffer**

## Comportamento

Grava os dois bitsets (raizes e "cryptex") na area de config dinamica do `DynamicRegion`, precedido de varias guardas:

1. Idempotencia: se `param_1+100 != 0`, ja foi setado, retorna.
2. So executa se `param_1+0x6c == 0` (ainda nao setado) e os dois spans tem exatamente `(param_2+7)>>3` bytes cada (linhas 23-24).
3. Calcula `lVar2 = firstFreeOffset`, `uVar1 = lVar2 + param_6`, e valida:
```
27:  if ((uVar1 >> 0x20 == 0) && (uVar1 + param_6 < 0x4001)) {
```
O primeiro teste rejeita overflow de 32 bits no offset do segundo bitset; o segundo garante que `offset_raizes + 2*tamanho < 0x4001`, ou seja tudo cabe nos 0x4000 bytes da area dinamica.

4. Varre os dois spans so para decidir flags (bit 4 se raizes nao-vazias, bit 8 se cryptex nao-vazio), depois `memmove` dos dois.

## Observacao

As checagens cobrem o essencial: tamanho exato dos spans, overflow do offset e limite superior do buffer. O uso de `firstFreeOffset` mais a comparacao `< 0x4001` (e nao `<=`) garante margem de 1. Nao ha defeito evidente; `param_2` (a contagem de entradas) vem do header e ja foi delimitado por `buildRootsBitmaps` a 1..65536, coerente com o teto de 0x4000 bytes (8192) dos bitsets.

## Classificacao final

- Sem defeito. Guardas de overflow e de limite presentes e corretas.
