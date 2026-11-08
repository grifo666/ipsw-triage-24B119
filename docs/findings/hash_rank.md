# hash_rank

- Simbolo: `__ZN6mach_oL9hash_rankENSt3__14spanIKhLm18446744073709551615EEE.c` (29 linhas), Ghidra headless
- Classificacao: **pre-condicao rigida; trap em span curto**

## Comportamento

```
if (param_2 < 0x58) { SoftwareBreakpoint(1,...); }   // trap se span < 0x58
lVar4 = -4;
do {
  if (hashPriorities[lVar3] == this[0x25]) return lVar4 + 5;  // rank 1..4
  lVar3++; bVar2 = lVar4 != -1; lVar4++;
} while (bVar2);
return 0;
```

Mapeia o byte de hashType em `this[0x25]` (offset 0x25 do blob de CodeDirectory) para um rank de prioridade 1..4 via a tabela `hashPriorities`; hashType desconhecido retorna 0.

## Observacao - trap em vez de erro

Se o span passado tiver menos de 0x58 bytes, a funcao nao retorna erro: executa `SoftwareBreakpoint` (trap `brk #1`), derrubando o processo. Ou seja, o chamador precisa garantir o tamanho minimo do CodeDirectory (0x58 = cabecalho ate o campo hashType em 0x25 mais folga). `forEachCodeDirectoryBlob` fornece esse span; se um blob de CD for truncado e chegar aqui com span menor, o resultado e crash, nao `nullopt`. Depende inteiramente da validacao a montante.

## Classificacao final

- Sem escrita, so leitura de `this[0x25]` apos a guarda de tamanho. O risco e o trap quando a montante nao garante span >= 0x58.

