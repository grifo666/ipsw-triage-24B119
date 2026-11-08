# Indice de findings

Triagem estatica do dyld shared cache iOS 27.2 (24B119) contra 26.6.1 (23G83), alvo iPhone18,2.

## Bug real

| Simbolo | Finding | Nota |
|---|---|---|
| preflightCacheFile | [preflightCacheFile](preflightCacheFile.md) | `mappingOffset` sem faixa; throw `bad_optional_access` alcancavel com count==1, 5 condicoes de header e mapping sem bit 7 ou com flag de auth GOT ligado; `count == 0` com array intocado quando todo mapping tem bit 7 e o flag esta desligado. **Herdado: identico na base 23G83, nao corrigido no 27.2.** Candidato mais forte |
| mapSplitCacheSystemWide | [mapSplitCacheSystemWide](mapSplitCacheSystemWide.md) | vaza fds no erro de subcache; 6o argumento e `loadInfo`, tipo correto |
| mapSplitCachePrivate | [mapSplitCachePrivate](mapSplitCachePrivate.md) | vaza fd no erro de subcache |

## Ponto fraco (nao bug confirmado)

| Simbolo | Finding | Nota |
|---|---|---|
| hash_rank | [hash_rank](hash_rank.md) | trap `brk` em span curto |
| forEachCodeDirectoryBlob | [forEachCodeDirectoryBlob](forEachCodeDirectoryBlob.md) | nao valida `cdLength >= 0x58`, entrega a `hash_rank` |
| preflightSubCacheFile | [preflightSubCacheFile](preflightSubCacheFile.md) | abre fd e nao fecha; alimenta o vazamento dos mappers |
| preflightMainCacheFile | [preflightMainCacheFile](preflightMainCacheFile.md) | abre fd principal e nao fecha; mesma origem |

## Robustos / sem defeito

| Simbolo | Finding |
|---|---|
| buildRootsBitmaps | [buildRootsBitmaps](buildRootsBitmaps.md) |
| setRootsBitmaps | [setRootsBitmaps](setRootsBitmaps.md) |
| mapSegments | [mapSegments](mapSegments.md) |
| validMagic | [validMagic](validMagic.md) |
| openat | [openat](openat.md) |
| isSubCachePath | [isSubCachePath](isSubCachePath.md) |
| loadDyldCache | [loadDyldCache](loadDyldCache.md) |
| forEachCDHashOfCodeSignature | [forEachCDHashOfCodeSignature](forEachCDHashOfCodeSignature.md) |
| restartWithDyldInCache | [restartWithDyldInCache](restartWithDyldInCache.md) |
| validSemanticsSegments | [validSemanticsSegments](validSemanticsSegments.md) |
| validStructureLoadCommands | [validStructureLoadCommands](validStructureLoadCommands.md) |
| lockdownDyldDataConst | [lockdownDyldDataConst](lockdownDyldDataConst.md) |
