# Loader::mapSegments

- Simbolo: `__ZN5dyld46Loader11mapSegmentsER11DiagnosticsRNS_12RuntimeStateEPKciyRKNS0_19CodeSignatureInFileEbNSt3__14spanIKNS0_6RegionELm18446744073709551615EEEbbRKNS0_18FileValidationInfoE.c` (240 linhas), Ghidra headless
- Classificacao: **robusto; `vm_deallocate` presente nos caminhos de falha**

## Comportamento

Mapeia as regioes de um Mach-O ja validado. Ordem: `validateFile`, checagem de assinatura (`registerSignature`/`fcntl F_ADDFILESIGS`), `vm_allocate` do tamanho total, loop de `mmap` por regiao, tratamento de FairPlay (`mremap_encrypted`) e de Rosetta AOT, e retorno do endereco base.

## Guardas e limpeza

- `validateFile` primeiro; aborta em erro (`Diagnostics::hasError`).
- Assinatura: caminho sem assinatura permitido so se `ProcessConfig` sinaliza (0x17b bit 0), senao erro explicito.
- `vm_allocate` conferido; falha -> erro e retorno 0.
- Cada `mmap` conferido; `MAP_FAILED` -> erro com errno/sandbox e `goto LAB_1804b11c8`, que faz `_vm_deallocate` da alocacao inteira antes de retornar 0.
- Primeira regiao checada com `isMachO`; `mremap_encrypted` e `rosetta_dyld_map_aot` conferidos, e a falha de FairPlay tambem cai no `vm_deallocate`.

## Observacao

O ponto que costuma falhar nesse tipo de funcao (liberar o `vm_allocate` no erro) esta tratado: o rotulo de erro de mmap e de FairPlay executa `vm_deallocate`. As falhas anteriores ao `vm_allocate` (validacao, assinatura, `vm_allocate` ele mesmo) nao tem o que liberar. Os tamanhos vem das `Region` do proprio binario ja validado, nao de header bruto sem checagem. Sem defeito evidente de memoria.

## Classificacao final

- Sem defeito. Limpeza de `vm_allocate` correta em todos os caminhos pos-alocacao; entradas validadas antes.
