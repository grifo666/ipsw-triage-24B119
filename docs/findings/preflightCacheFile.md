# preflightCacheFile

- Simbolo: `__ZN5dyld3L18preflightCacheFileERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoEPNS_9CacheInfoEiPNSt3__15arrayIA32_cLm128EEEPKS3_.c`
- Build: iOS 27.2 (24B119), base 26.6.1 (23G83), alvo iPhone18,2
- Fonte: `06-decomp/dyld/__ZN5dyld3L18preflightCacheFile...c` (310 linhas), Ghidra headless
- Classificacao: **bug real de robustez (validacao insuficiente do header), com um caminho de crash alcancavel**

## Contexto

A funcao le 0x4000 bytes fixos do offset 0 do arquivo de cache num buffer de stack:

```
80:    sVar13 = _pread(iVar11,local_4070,0x4000,0);
81:    if (sVar13 != 0x4000) { ... pread() failed ... }
```

`local_4070` e o offset 0 do header; o buffer cobre 0x4070..0x8070. Todos os campos abaixo sao lidos do header sem que o buffer seja validado contra eles.

## Ponto 1 - mappingOffset sem validacao de faixa

`mappingOffset` e o uint32 no header+0x10 (aqui `local_4060`, em 0x4060, isto e, buffer+0x10). O codigo o usa direto como base do array de mappings, sem checar faixa, alinhamento nem minimo:

```
103:    uVar21 = (ulong)local_4060;
104:    lVar9 = uVar21 - 0x4070;
105:    plVar1 = (long *)((long)local_4070 + (ulong)(local_405c - 1) * 0x20 + lVar9 + 0x4070);
189:    puVar3 = (undefined8 *)((long)local_4070 + uVar26 * 0x20 + lVar9 + 0x4070);
```

O i-esimo mapping cai em `buffer + mappingOffset + i*0x20`. Se `mappingOffset > 0x4000`, os acessos saem do buffer de 0x4000 e leem stack nao inicializada acima dele (o array `alStack_4050`/`local_4070` fica em 0x4070..). Nao ha clamp contra `mappingOffset + mappingCount*0x20 <= 0x4000`. Confirmado: **bug real**, o header controla o indice do buffer.

## Ponto 2 - o range check de mappingCount (PREMISSA CORRIGIDA)

`mappingCount` e o uint32 em header+0x14 (`local_405c`, 0x405c = buffer+0x14). O check:

```
99:    if (local_405c - 9 < 0xfffffff8) {
100:      pcVar19 = "shared cache file mappings are invalid";
101:      goto LAB_18050a234;
```

Rodei a aritmetica de 32 bits: `count-9 < 0xfffffff8` aceita **1..8** e rejeita **0 e >=9**. Ou seja, ha piso (1) **e teto (8)**. Isto contradiz a premissa de "rejeita 1..8, aceita 0 ou >=9, sem teto".

Consequencia: cada iteracao escreve um slot de 0x30 em `param_3 + i*0x30` e o contador final em `param_3+0x180` (linha 253).

### Tamanho real do CacheInfo (medicao)

O struct tem **0x1c0 bytes**. Prova: o ultimo campo escrito e `param_3+0x1b8` (8 bytes, linha 176), e o chamador copia exatamente 0x1c0 bytes:

```
425 (mapSplitCachePrivate):  __platform_memmove(local_e190,local_ea00,0x1c0);
```

O array de mappings ocupa os primeiros **8 slots de 0x30 = 0x180**. O campo `count` fica em 0x180, logo apos o array, seguido do fd (0x188) e dos campos de cauda (0x198..0x1b8). Um 9o mapping cairia em 0x180..0x1af e sobrescreveria `count`, `fd` e os campos de cauda — ou seja, **count>=9 transbordaria o array**. Mas o range check rejeita >=9, entao na pratica o array e exatamente do tamanho do teto e nao estoura.

Conclusao do item: o array **nao e maior que 0x180**, e tem exatamente 0x180 (8 slots). O teto do range check (8) coincide com o tamanho do array, coerente. O transbordo so ocorreria se o teto fosse removido.

## Ponto 3 - mappingWithSlideOffset/Count como indice sem checagem

`mappingWithSlideOffset` e o uint32 em header+0x138 (`local_3f38` = buffer+0x138). Ele indexa um segundo array, com stride 0x38, tambem sem validacao:

```
192:    lVar7 = uVar26 * 0x38 + ((ulong)local_3f38 - 0x4070);
206:    lVar6 = *(long *)((long)auStack_4058 + lVar7 + 0x4070);
207:    lVar7 = *(long *)((long)alStack_4050 + lVar7 + 0x4070);
```

O segundo array baseia-se em `buffer + mappingWithSlideOffset`, entao o mesmo problema do Ponto 1 se aplica e ainda sem o teto do count. **bug real**.

## Ponto 4 - o throw std::bad_optional_access E alcancavel (PREMISSA CORRIGIDA)

`bVar8` controla o throw:

```
225:                  if (lVar7 != 0) {
226:                    if (!bVar8) {
228:                      std::__throw_bad_optional_access_abi_nqn220106_();
```

`bVar8` e posto true em LAB_18050a2f8 (linha 128), alcancado quando `local_405c >= 2`; e false em LAB_18050a308 (linha 119), alcancado quando `local_405c < 2`, isto e, **count == 1** (0 ja foi rejeitado). Como o range check aceita 1..8, count==1 passa e chega em bVar8=false.

Mas bVar8=false sozinho nao basta. O throw exige cinco condicoes simultaneas:

1. `mappingCount == 1`.
2. `mapping[0].fileOffset == 0` (linha 107 le o campo; a string sai na 123), senao "shared cache text file offset is invalid".
3. faixa de assinatura igual a `st_size` (linha 108), senao "shared cache code signature size is invalid" (linha 109).
4. permissoes iguais a 5 (linha 131), senao "shared cache text permissions are invalid" (linha 132).
5. o primeiro campo da entrada de linkedit do mapping diferente de zero (linha 225,
   `lVar7`, calculado na linha 192 sobre `alStack_4050 + linkeditOffset + idx*0x38`).

As condicoes 2 a 4 existem porque o laco inteiro, e o throw com ele, esta dentro de `if (*(long *)(lVar17 + 0x10) == 0)` (linha 134), ou seja, so roda quando nenhuma string de erro foi gravada. A condicao 5 e o `if (lVar7 != 0)` que envolve o throw.

Falta ainda um sexto cuidado, e a condicao e mais estreita do que parece: o mapping so e descartado quando o bit 7 (`uVar14 >> 7 & 1`, linha 212) esta ligado **e** o flag de auth GOT esta **desligado**. A linha 212 desvia para a copia quando o bit 7 esta limpo; o `else` (linha 239) so faz `goto` para a copia se `SVar25 & 1` (linha 240), e `SVar25` vem de `param_6[0x19]` (linha 180). Ou seja, com o flag desligado um mapping de auth GOT pula a copia e o throw nao e alcancado; com o flag ligado ele e copiado e o throw dispara normalmente.

Atendidas todas, o laco roda uma vez e o throw dispara logo depois de copiar o mapping para o `CacheInfo` (linha 215). Ou seja: **um cache de 1 mapping com fileOffset 0, assinatura e permissoes coerentes e linkedit nao-vazio derruba o processo com excecao**, sem nenhuma string de erro setada. O throw **nao** e inalcancavel. A premissa de que o piso de 9 (na verdade teto) tornaria o throw morto esta errada porque o throw depende de count<2, nao de count<9.

## Classificacao final

- Ponto 1 (mappingOffset sem faixa): bug real de robustez, leitura fora do buffer.
- Ponto 2 (count): **corrigido** — ha teto 8, slots nao transbordam.
- Ponto 3 (mappingWithSlideOffset/Count): bug real, mesmo vetor do Ponto 1 e sem teto.
- Ponto 4 (throw): **corrigido** — alcancavel com count==1, fileOffset==0, assinatura e permissoes coerentes, linkedit[0] != 0 e mapping fora de auth GOT; crash por excecao nao tratada.

Candidato a validacao no aparelho: forjar um header de cache com `mappingOffset` grande (ou `mappingWithSlideOffset` grande) mantendo `mappingCount` em 1..8, e um caso count==1 com fileOffset 0, assinatura e permissoes coerentes e linkedit preenchido, para exercitar o throw.