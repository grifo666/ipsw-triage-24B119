# validStructureLoadCommands

- Simbolo: `__ZNK6mach_o6Header26validStructureLoadCommandsEy.c` (const member; o lote anterior usou `__ZN` sem o `K` e falhou)
- Build: iOS 27.2 (24B119), base 26.6.1 (23G83), alvo iPhone18,2
- Fonte: `06-decomp/dyld/...validStructureLoadCommands...c` (306 linhas), Ghidra headless
- Classificacao: **robusto; validacao estrutural, nenhum bug forte**

## Guardas presentes

1. Tamanho minimo do header (linha 102): `*(ulong *)(param_1 + 8) < 0x1c` cai em `SoftwareBreakpoint(1)` em `:104`. `param_1 + 8` e o comprimento do arquivo.
2. Tamanho dos comandos contra o arquivo (linha 111): `in_x1 < (uint)(iVar3 + mach_header[5])` emite "load commands length (%llu) exceeds length of file (%llu)". `in_x1` e o tamanho do arquivo recebido, `mach_header[5]` e `sizeofcmds`.
3. Enumeracao delegada (linha 203): `forEachLoadCommand` percorre os comandos; cada um incrementa um contador por tipo via bloco.
4. Unicidade por tipo (linhas 205-285): uma cadeia de `if (count < 2)` garante que cada comando singleton (`LC_SYMTAB`, `LC_DYSYMTAB`, `LC_SEGMENT_SPLIT_INFO`, `LC_ATOM_INFO`, `LC_FUNCTION_STARTS`, `LC_DYLD_EXPORTS_TRIE`, `LC_DYLD_CHAINED_FIXUPS`, `LC_FUNCTION_VARIANTS`, `LC_FUNCTION_VARIANT_FIXUPS`, `LC_TARGET_TRIPLE`, `LC_ID_DYLIB`, `LC_ENCRYPTION_INFO_64`, `LC_DYLD_INFO`, `LC_MAIN`/`LC_UNIXTHREAD`, `LC_ROUTINES[_64]`) apareca no maximo uma vez, com mensagem especifica por tipo.
5. Erro do `forEachLoadCommand` propagado (linha 205): `local_f8 + 0x19 != 0` copia o erro e pula a checagem de unicidade.

## Nota

A checagem de unicidade e uma escada linear de ate 16 comparacoes por header, custo desprezivel. O limite de `sizeofcmds` vem do proprio header (`mach_header[5]`); como `validStructureLoadCommands` recebe o tamanho do arquivo em `in_x1` e compara, um `sizeofcmds` forjado maior que o arquivo e barrado antes de qualquer leitura em `forEachLoadCommand`. Sem bug.

A logica por comando vive no bloco `_block_invoke` do mesmo simbolo; este corpo so conta e checa unicidade. A profundidade da validacao por comando (offsets, sizes internos) fica no bloco, fora deste arquivo.
