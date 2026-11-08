# preflightCacheFile: 23G83 (base) contra 24B119 (alvo)

Diff bruto: `preflightCacheFile.diff-23G83-24B119.txt` nesta pasta.
Artefatos: `06-decomp/dyld/23G83__ZN...EEE.c` (base, 310 linhas) e
`06-decomp/dyld/__ZN...EEEPKS3_.c` (alvo, 262 linhas).

O nome mangled muda entre as builds. A base tem 5 parametros, o alvo tem 6:

- base: `preflightCacheFile(SharedCacheOptions const&, SharedCacheLoadInfo*, CacheInfo*, int, std::array<char[32],128>*)`
- alvo: o mesmo mais `SharedCacheLoadInfo const*` no 6o

Assinatura de simbolo diferente e sinal de mudanca de ABI interna, nao de build nova.

## 1. Assinatura e o novo 6o parametro (novo no alvo)

O alvo le `param_6[0x19]` (byte 0x19) e sobrescreve a decisao de incluir mappings de
auth GOT:

```
179:            if (param_6 != (SharedCacheLoadInfo *)0x0) {
180:              SVar25 = param_6[0x19];
```

`SVar25` tambem e gravado em `lVar17+0x19` (o mesmo byte do `options`), ou seja, a
funcao propaga o flag para o chamador e o 6o argumento serve para herdar o valor ja
decidido pelo chamador pai, em vez de recalcular.

Consequencia: `param_6` e `SharedCacheLoadInfo const*` e o unico campo lido e o byte
0x19, o mesmo que a funcao escreve em `options+0x19`. A nota anterior de que
`mapSplitCacheSystemWide` passa `loadInfo` num 6o argumento "incompativel com
`SharedCacheOptions*`" fica corrigida: `loadInfo` e exatamente o tipo do 6o parametro.

Conferido nos dois chamadores no 27.2: `mapSplitCacheSystemWide` passa `pSVar13` e
`mapSplitCachePrivate` passa `local_e840`, ambos declarados `SharedCacheLoadInfo*`.
`preflightSubCacheFile` declara `SharedCacheLoadInfo const*` no 6o e repassa `param_6`.
Os tres pontos usam o mesmo tipo, sem cast nem troca de significado.

## 2. `validMagic` deixa de ser inline

Base:

```
if (local_4070[0] == 0x2031765f646c7964 && local_4070[1] == 0x6534366d726120)
```

Alvo:

```
121:    uVar14 = validMagic((SharedCacheOptions *)local_4070,extraout_x1);
```

Ganho: a validacao de magic deixa de ser um par de constantes soltas no corpo e passa
a aceitar as variantes reconhecidas por `validMagic`. Nao fecha o problema de faixa do
`mappingOffset` (item 4).

## 3. Gate de tamanho removido (regressao de robustez)

A base so olhava plataforma quando o `mappingOffset` era grande, e so lia entradas de
subcache quando o header era grande o bastante:

```
base 110:        if (0xdf < local_4060) {
base 393:        param_3[0x185] = (CacheInfo)(0x1c8 < local_4060);
base 394:        if (0x1c8 < local_4060) {
```

O alvo remove os tres gates: a checagem de plataforma roda sempre e o `pread` de
0x1c00 das entradas de subcache roda sempre que `subcacheCount != 0`:

```
257:                  sVar13 = _pread(iVar11,auStack_5ca8,0x1c00,(ulong)local_3ee8);
```

Isto e mais correto para caches legitimamente pequenos, mas tira a ultima barreira que
impedia o `pread` de ser guiado por `subcacheOffset`/`subcacheCount` de um header
forjado. O campo `param_3[0x185]` (o "tem subcaches") desaparece do struct no alvo.

## 4. `mappingOffset` continua sem validacao de faixa (bug herdado, nao corrigido)

O indice do buffer segue sendo `buffer + mappingOffset + i*0x20`, sem clamp, identico
nas duas builds:

```
base 105:    plVar1 = (long *)((long)local_4070 + (ulong)(local_405c - 1) * 0x20 + lVar9 + 0x4070);
alvo 104:    plVar1 = (long *)((long)local_4070 + (ulong)(local_405c - 1) * 0x20 + lVar9 + 0x4070);
```

O mesmo vale para `mappingWithSlideOffset`, que indexa com stride 0x38:

```
alvo 192:    lVar7 = uVar26 * 0x38 + ((ulong)local_3f38 - 0x4070);
```

Nao e regressao: o defeito existe igual nas duas builds. E o vetor de leitura fora do
buffer de 0x4000 descrito no finding principal.

## 5. Overlap check reescrito (equivalente)

Base:

```
if ((ulong)(lVar16 + *plVar1) <= *puVar2) goto code_r0x00018019b708;
code_r0x00018019b708: uVar20 = uVar20 + lVar16; ... if (uVar20 != puVar2[2]) goto LAB_...71c;
```

Alvo, numa comparacao so:

```
if ((*puVar30 < (ulong)(lVar7 + *plVar2)) ||
   (uVar14 = uVar14 + lVar7, uVar14 != puVar30[2])) {
```

Mesma semantica (fim do mapping anterior <= inicio do proximo, e fim de texto
encadeado igual ao fileOffset), so que sem o bloco intermediario. Tambem
`param_3[0x184]` passa a ler `lVar23+0xb` em vez de `lVar23+0xc`.

## 6. Filtro de mapping de auth GOT (novo no alvo)

O alvo pula mappings marcados com `uVar14 >> 7 & 1` (linha 212) quando o flag de auth
GOT esta ligado, com log:

```
242:                      dyld4::console("  including auth GOT mapping\n");
247:                    dyld4::console("  skipping auth GOT mapping\n");
```

E o `count` gravado em `param_3+0x180` passa a ser o contador do laco (`iVar10`,
incrementado so nos mappings copiados), escrito depois do laco:

```
alvo 253:            *(int *)(param_3 + 0x180) = iVar10;   // apos o laco, so copiados
base 144:            *(uint *)(param_3 + 0x180) = local_405c;  // antes do laco, todos
```

A base grava o total de mappings de forma incondicional (linha 144) e so entra no laco
com `local_405c != 0`; como nao ha filtro, `count` e sempre o total e o array so fica
intocado quando o total ja era zero. O alvo conta apenas o que copiou.

O filtro so descarta quando o flag esta **desligado**. O teste da linha 240 e
`if (((byte)SVar25 & 1) != 0)` e, quando verdadeiro, faz `goto LAB_18050a544`, isto e,
inclui o mapping normalmente; o `else` (linha 244) e que so loga "skipping auth GOT
mapping" e nao copia. `SVar25` vem da linha 177 e e sobrescrito por `param_6[0x19]` na
180, ou seja, e o byte de decisao do cache principal, o mesmo que o `preflightSubCacheFile`
herda.

Consequencia nova: no alvo, com `local_405c > 0`, todos os mappings com o bit 7 ligado e
o flag desligado, todos caem no `else` da linha 239, nada e copiado, e a linha 253 grava
`count == 0` mesmo havendo mappings. O array nao e zerado antes do laco (nenhum
`bzero`/`memset` em nenhuma das duas builds), mas como nada foi escrito o chamador
recebe `CacheInfo` com zero entradas. A funcao retorna sucesso.

Isso e diferente do caso do item 7: ali o throw interrompe antes da linha 253, entao
`param_3+0x180` nem chega a ser gravado.

## 7. Throw `bad_optional_access` mantido

O throw sobrevive no alvo, na mesma condicao:

```
alvo 228:                      std::__throw_bad_optional_access_abi_nqn220106_();
```

Pre-condicoes exatas, identicas nas duas builds (na base o throw esta na linha 201, com
`lVar13` no lugar de `lVar7`):

1. `bVar8 == false`, o que so acontece quando `local_405c <= 1`: com `1 < local_405c`
   o fluxo salta para `LAB_18050a2f8` (linha 127) e liga `bVar8 = true` (linha 128).
   `bVar8 = false` fica na linha 119, sob o rotulo `LAB_18050a308` (linha 118). Na
   pratica, `mappingCount == 1`.
2. `mapping[0].fileOffset == 0` (o campo e lido na linha 106 e testado na 107), senao a
   string de erro sai na 123 e o laco nao roda.
3. faixa de assinatura igual a `st_size` (linha 108).
4. permissoes iguais a 5 (linha 131).
5. `lVar7 != 0` (linha 225), sendo `lVar7` o primeiro campo da entrada de linkedit: o
   indice sai na linha 192 e o campo e carregado na 207 a partir de `alStack_4050`. O
   header precisa apontar um linkedit de tamanho nao-zero.

As condicoes 2 a 4 valem porque o laco esta dentro de `if (*(long *)(lVar17 + 0x10) == 0)`
(linha 134). Falta ainda uma sexta: o mapping nao pode ser de auth GOT com o flag
**desligado**. A linha 212 desvia para a copia quando `uVar14 >> 7 & 1` esta limpo; com o
bit 7 ligado o fluxo cai no `else` da linha 239, e ali a linha 240 testa `SVar25 & 1`:
ligado faz `goto` para a copia (throw preservado), desligado so loga "skipping" e nao
copia. `SVar25` e o `param_6[0x19]` da linha 180.

Atendidas todas, o throw dispara logo apos copiar o mapping (linha 215). So muda o
sufixo ABI (`nqn210106` na base, `nqn220106` no alvo). O caminho de crash do finding
principal continua valido no 27.2.

## Classificacao do diff

- Herdado e nao corrigido: item 4 (`mappingOffset`/`mappingWithSlideOffset` sem faixa)
  e item 7 (throw alcancavel com count==1).
- Regressao de robustez: item 3 (gates de tamanho removidos; `pread` guiado por header
  forjado agora e incondicional).
- Novo comportamento a explorar: item 1 (6o parametro que herda o flag de auth GOT) e
  item 6 (`count == 0` com array intocado quando tudo e auth GOT).
- Neutro/melhoria: itens 2 e 5.

## Correcao de nota anterior

A pendencia de AGENTS.md dizia que `mapSplitCacheSystemWide` passava `loadInfo` no 6o
argumento "incompativel com `SharedCacheOptions*`". O 6o parametro de
`preflightCacheFile` no alvo e `SharedCacheLoadInfo const*`, entao `loadInfo` e o tipo
certo. `preflightSubCacheFile` tambem declara `SharedCacheLoadInfo const*` no 6o, de
modo que o passthrough e tipado corretamente nos tres pontos.

O valor tambem fecha. O byte 0x19 e escrito no proprio `param_2` (o `loadInfo`), e o
`preflightCacheFile` do cache principal roda antes do loop de subcaches com esse mesmo
`loadInfo`:

- `mapSplitCacheSystemWide`: `preflightMainCacheFile(pSVar9,pSVar13,...)` na linha 327
  e `preflightSubCacheFile(...,pSVar13)` na 352, mesmo ponteiro.
- `mapSplitCachePrivate`: `preflightMainCacheFile(pSVar18,...)` na 376 e
  `preflightSubCacheFile(...,local_e840)`, com `local_e840 = pSVar18` na 375.

Ou seja, o main grava `lVar17+0x19` e o subcache le `param_6[0x19]`, o mesmo byte do
mesmo struct. O 6o argumento existe para o subcache nao recalcular a decisao de auth
GOT do zero e seguir a do main. Sem defeito de tipo nem de valor.