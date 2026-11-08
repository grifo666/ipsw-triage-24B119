# validSemanticsSegments

- Simbolo: `__ZNK6mach_o6Header22validSemanticsSegmentsERKNS_6PolicyEy.c` (const member; o lote anterior usou `__ZN` sem o `K` e falhou)
- Build: iOS 27.2 (24B119), base 26.6.1 (23G83), alvo iPhone18,2
- Fonte: `06-decomp/dyld/...validSemanticsSegments...c` (295 linhas), Ghidra headless
- Classificacao: **robusto; validacao de segmentos densa, nenhum bug forte**

## Guardas presentes

1. Tamanho minimo do header (linha 117): `*(ulong *)(param_1 + 8) < 0x1c` desvia para `SoftwareBreakpoint(1)` em `:236`. `param_1 + 8` e o comprimento do arquivo; a mesma checagem se repete antes de cada leitura de campo (`:147`, `:161`, `:181`, `:214`, `:233`, `:257`, `:264`).
2. Laco de comandos de carga (linha 125): condiciona a `uVar13 + 8 < size`, entao nunca le um `cmdsize` colado no fim do buffer.
3. Validacao do `cmdsize` (linha 129): `uVar3 < 8 || (uVar3 & 3) != 0 || size < uVar9 || uVar9 < uVar13`. Rejeita tamanho curto, desalinhado, que passa do arquivo, e detecta overflow de `uVar13 + uVar3`.
4. Teto de segmentos (linha 143): `0xff < count` dispara "too many segments %llu (max 255)".
5. `__TEXT` com `fileOffset != 0` (linha 157): erro explicito.
6. Comandos que nao cabem no `__TEXT` (linhas 172 e 180): testa contra filesize e vmsize do segmento.
7. Sobreposicao entre segmentos (linhas 210 e 215): ranges de vm e de arquivo, par a par.
8. Nome de segmento duplicado (linha 220): `__platform_memcmp` com os mesmos tamanhos.
9. Ordem de offsets (linha 251): "segment file offset out of order".

## Nota

O `SoftwareBreakpoint(1)` em `:236` e alcancado por `goto` mesmo com `size` ja validado no topo. Como o tamanho nao muda, o trap e efetivamente defesa redundante: nao ha caminho que chegue em `:236` com `size < 0x1c`. Sem bug.

O laco aninhado de sobreposicao (linhas 208-230) e O(n^2) com `n <= 255`, custo maximo ~65k comparacoes por header: sem risco de tempo.