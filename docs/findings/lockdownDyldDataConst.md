# lockdownDyldDataConst (bloco)

- Simbolo: `____ZN5dyld4L21lockdownDyldDataConstEPKN6mach_o12UnsafeHeaderE_block_invoke` (o corpo principal e `static` e foi totalmente inlineado; so o bloco sobrevive como simbolo)
- Build: iOS 27.2 (24B119), base 26.6.1 (23G83), alvo iPhone18,2
- Fonte: `06-decomp/dyld/...lockdownDyldDataConst..._block_invoke.c` (15 linhas), Ghidra headless
- Classificacao: **robusto; helper de `mprotect` sobre `__DATA_CONST`**

## Comportamento

O bloco recebe o contexto em `param_1` e a descricao do segmento em `param_2`:

```
6:  if ((*(byte *)(param_2 + 0x28) >> 4 & 1) == 0) return;   // bit 4: segmento e __DATA_CONST
11: ...mprotect(sSyscallDelegate, base + vmOffset, vmSize, 1);  // 1 = PROT_READ
```

- `param_1 + 0x20`: base do cache mapeado.
- `param_2 + 0x10`: deslocamento do segmento.
- `param_2 + 0x18`: tamanho do segmento.
- `param_2 + 0x28` bit 4: so age quando o segmento e `__DATA_CONST`.
- Protecao fixa em `1` (`PROT_READ`): remove escrita apos o rebase/bind, o "lockdown" do nome.

## Nota

O bloco nao revalida a faixa `base + vmOffset, vmSize`: confia no chamador (a enumeracao de segmentos de `handleDyldInCache`). `mprotect` arredonda para paginas e so age na VM ja mapeada, entao um `vmOffset`/`vmSize` estranho faz o `mprotect` falhar silenciosamente (retorno ignorado) ou cobrir paginas vizinhas ja mapeadas. Nao ha desmapeamento nem leitura aqui; o risco e baixo.

Como o corpo de `lockdownDyldDataConst` foi inlineado, a recuperacao da logica completa exigiria decompilar `handleDyldInCache`, que tambem nao tem simbolo proprio (so blocos `_block_invoke`). Fica como proximo passo se o helper precisar de contexto.