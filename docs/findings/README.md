# Findings

Triagem estatica do `dyld` do iOS 27.2 (24B119, alvo iPhone18,2) contra a base 26.6.1 (23G83). Cada arquivo cobre um simbolo, com o trecho decompilado, o numero de linha e o raciocinio. O indice classificado fica em [INDEX.md](INDEX.md).

## Bug real

Tres defeitos com sustentacao no decompilado.

### 1. preflightCacheFile: validacao de header insuficiente e throw alcancavel

[preflightCacheFile](preflightCacheFile.md). O buffer do header e um `pread` fixo de 0x4000 no offset 0. `mappingOffset` (header+0x10) e `mappingWithSlideOffset` (header+0x138) entram como base crua de arrays, sem checagem de faixa, alinhamento ou minimo. Um valor grande le o array acima do buffer, em stack nao inicializada.

O `throw std::bad_optional_access` em `:228` e alcancavel, mas so quando nenhuma string de erro foi gravada, porque o laco inteiro esta sob `if (*(long *)(lVar17 + 0x10) == 0)`. Com `mappingCount == 1` isso exige o primeiro `fileOffset == 0`, assinatura coerente com o tamanho do arquivo e permissoes 5; atendido isso, `bVar8` fica false em `:119` e um slide nao nulo em `:225` mata o processo. E o candidato mais forte a validacao no aparelho.

### 2. mapSplitCacheSystemWide: vazamento de file descriptors

[mapSplitCacheSystemWide](mapSplitCacheSystemWide.md). Cada fd aberto ate o ponto de falha vaza nas duas saidas de erro (preflight de subcache e `DynamicRegion::make`), em `:355` e `:362`. So o caminho de sucesso tem o laco de `close` em `:473-482`.

### 3. mapSplitCachePrivate: vazamento de file descriptor

[mapSplitCachePrivate](mapSplitCachePrivate.md). Mesmo defeito no caminho de falha de preflight de subcache: o `goto LAB_180508a30` em `:412` nao fecha nada.

## Ponto fraco (nao bug confirmado)

- [hash_rank](hash_rank.md): dispara `SoftwareBreakpoint(1)` se o span for menor que 0x58.
- [forEachCodeDirectoryBlob](forEachCodeDirectoryBlob.md): nao valida `cdLength >= 0x58` antes de entregar a `hash_rank`; a guarda vive no chamado.
- [preflightSubCacheFile](preflightSubCacheFile.md): abre o fd do subcache e nao fecha; alimenta os dois vazamentos acima.
- [preflightMainCacheFile](preflightMainCacheFile.md): dono do fd principal; mesma origem do vazamento.

## Robustos / sem defeito

- [buildRootsBitmaps](buildRootsBitmaps.md): faixa de contagem 1..65536, checagem de tamanho do pread, clamp de mmap, `munmap` no fim.
- [setRootsBitmaps](setRootsBitmaps.md): guarda de overflow 32 bits e limite `< 0x4001`.
- [mapSegments](mapSegments.md): `vm_deallocate` em todos os caminhos de falha.
- [validMagic](validMagic.md): laco limitado a 4 arquiteturas.
- [openat](openat.md): retry restrito a EAGAIN/EINTR.
- [isSubCachePath](isSubCachePath.md): heuristica simples, sem bug de memoria.
- [loadDyldCache](loadDyldCache.md): dispatcher puro (privado vs systemwide).
- [forEachCDHashOfCodeSignature](forEachCDHashOfCodeSignature.md): stub de encaminhamento.
- [restartWithDyldInCache](restartWithDyldInCache.md): stub de salto indireto; corpo nao recuperado, inconclusivo quanto a logica.
- [validSemanticsSegments](validSemanticsSegments.md): guarda de header, `cmdsize` (curto, desalinhado, overflow), teto de 255 segmentos, sobreposicao vm/arquivo, nome duplicado.
- [validStructureLoadCommands](validStructureLoadCommands.md): `sizeofcmds` contra o tamanho do arquivo e unicidade por tipo de comando.
- [lockdownDyldDataConst](lockdownDyldDataConst.md): bloco `mprotect(PROT_READ)` restrito a `__DATA_CONST`; nao revalida faixa, mas o risco e baixo.

## Candidato a validacao no aparelho

`preflightCacheFile`, com um header de cache forjado: `mappingOffset` ou `mappingWithSlideOffset` grande o bastante para sair do buffer de 0x4000, com `mappingCount` entre 1 e 8. Repetir com `mappingCount == 1`, primeiro `fileOffset == 0`, assinatura coerente e slide nao nulo para acionar o `bad_optional_access`. Observar panic ou leitura de lixo.

## Metodo

Analise so estatica, sem runtime. Cada veredito e ancorado em linha do decompilado; onde o decompilado nao sustenta a conclusao, o arquivo diz "inconclusivo" e aponta o que falta. As guardas benignas ficam registradas para nao serem re-litigadas.