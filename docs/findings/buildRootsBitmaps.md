# buildRootsBitmaps

- Simbolo: `__ZN5dyld3L17buildRootsBitmapsERKN5dyld413ProcessConfigEPN15DyldSharedCache13DynamicRegionEiRK17dyld_cache_headerbb.c`
- Build: iOS 27.2 (24B119), base 26.6.1 (23G83), alvo iPhone18,2
- Fonte: `06-decomp/dyld/__ZN5dyld3L17buildRootsBitmaps...c` (154 linhas), Ghidra headless
- Classificacao: **robusto; nenhum bug forte, apenas pressao de stack delimitada**

## Entradas do header

- `param_4 + 0x1c4`: contagem de entradas (`uVar11`), usada para dimensionar dois bitsets e o vetor de registros.
- `param_4 + 0x1c0`: offset no arquivo de onde os registros sao lidos.

## Guardas presentes

1. Faixa da contagem (linha 41):
```
41:  if (*(uint *)(param_4 + 0x1c4) - 0x10001 < 0xffff0000) goto LAB_18050ab4c;
```
Aritmetica de 32 bits: aceita **1..65536** (0x10000), rejeita 0 e >65536. Confirmado por conta direta: `x-65537` unsigned cai em `[0xffff0000,0xffffffff]` exatamente para `x` em `[1,65536]`. Isso delimita `uVar11` antes de qualquer alocacao.

2. Bitsets dimensionados por `uVar9 = uVar11+7 >> 3` (linha 42), no maximo 8192 bytes cada, e zerados com `__bzero` (48-49).

3. Vetor de registros: `sVar10 = uVar11 * 0x20` (linha 53), no maximo 2 MiB. `pread` e conferido byte a byte:
```
57:  param_1 = _pread(param_3,pbVar14,sVar10,*(uint *)(param_4 + 0x1c0));
58:  if (param_1 != (ProcessConfig *)(uVar11 * 0x20)) goto LAB_18050ab4c;
```

4. `fstat` e `mmap` conferidos; tamanho de leitura de strings limitado por `local_5a0` e `strnlen`:
```
71:  if ((uVar4 != 0) || (sStack_500.st_size < 1)) goto LAB;
78:  if (param_1 == 0xffffffffffffffff) goto LAB;
90:  if (uVar7 <= local_5a0 && sVar10 != 0) { ... strnlen ... }
```

## Observacao - pressao de stack

O `alloca` de `uVar11 * 0x20` (linha 54) chega a **2 MiB** no pior caso (65536 entradas), somado aos dois bitsets. E um `alloca` de tamanho controlado pelo header, porem dentro do teto imposto pela faixa. Caches legitimos tem poucas dezenas de entradas, entao na pratica e pequeno; um header forjado no teto ainda cabe no stack padrao (8 MiB no main thread). Nao estoura, mas consome stack proporcional ao header.

## Classificacao final

- Sem defeito de memoria. O vetor de ataque (contagem/offset do header) e validado. O unico custo e o `alloca` proporcional ao header, limitado a 2 MiB.
