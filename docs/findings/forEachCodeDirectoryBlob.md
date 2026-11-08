# forEachCodeDirectoryBlob

- Simbolo: `__ZN6mach_o5Image24forEachCodeDirectoryBlobEPKNS_6HeaderENSt3__14spanIKhLm18446744073709551615EEEU13block_pointerFvS7_E.c` (117 linhas), Ghidra headless
- Classificacao: **robusto com guardas de faixa; dependencia do trap de `hash_rank`**

## Comportamento

Varre a lista de blobs de superblob de assinatura (count big-endian em `param_1[2]`, com swap de bytes). Para cada entrada, le offset/tamanho (swap) e valida contra o span `param_3` antes de tocar:

```
32:  if (uVar17 <= param_3 - 0xc >> 3) {          // count cabe no span
44:  uVar10 <= param_3 - 0x58                      // offset deixa >= 0x58 bytes
...
62:  if (uVar9 < 4) trap;                          // cabe o magic
64:  if (*piVar1 == 0x20cdefa) {                   // magic de CodeDirectory
65:    if (uVar9 < 0x58) trap;
66:    uVar10 = comprimento do CD (swap)
68:    if (uVar10 <= uVar9) {                       // comprimento do CD cabe no restante
```

Quando o binario e executavel principal (`uVar13 == 1`) invoca o bloco direto; senao seleciona o CD de maior prioridade via `hash_rank`, comparando o atual com o anterior e mantendo o melhor, e ao fim emite o escolhido.

## Observacao - comprimento de CD e o trap de `hash_rank`

A guarda `uVar9 < 0x58` protege o **restante** do span, nao o **comprimento declarado do CD** (`uVar10`). O unico teste sobre `uVar10` e `<= uVar9` (cabe). Se um blob malformado declarar `cdLength < 0x58` mas ainda couber no restante, `hash_rank(piVar1, uVar10)` e chamado com span curto e dispara o trap `brk` (ver hash_rank.md), derrubando o processo em vez de pular o blob. CDs legitimos tem >= 0x58, entao na pratica so cabe a malformacao. A defesa fica inteiramente no trap de `hash_rank`, sem checagem local de tamanho minimo.

## Classificacao final

- Sem escrita fora do span; todas as leituras sao limitadas por `param_3`. O ponto fraco e nao validar `cdLength >= 0x58` antes de entregar a `hash_rank`, cujo trap derruba o processo.
