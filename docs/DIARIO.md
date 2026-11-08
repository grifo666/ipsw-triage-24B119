# Diario de sessao

Append-only. Uma entrada por passo, com hora. O que foi tentado, o que funcionou, o que foi descartado e por que. Commitar a cada entrada: e isto que faz a memoria sobreviver.

## 2026-11-07
- Push por simbolo quebrado: o push estava dentro do else de "nada a commitar". Movido para dentro do laco. 40a76e3.
- Workflow rejeitado por chave YAML duplicada (permissions). Bloco velho removido.
- Batch de 15 simbolos redisparado; os 15 chegaram em origin.
- Triagem dos 16 .c concluida, 19 findings escritos.
- Premissa corrigida: mappingCount aceita 1..8, rejeita 0 e >=9. CacheInfo 0x1c0, array de 8 slots, sem transbordo.
- Premissa corrigida: o throw exige fileOffset==0, nao !=0; o laco esta sob o teste de string de erro.
- Achados reais: offset sem validacao, throw alcancavel, vazamento de fd nos dois mappers.
- Regras novas: linguagem simples, passos numerados, execucao ao vivo sem tail.

## 2026-11-08
- Decompilacao do 26.6.1 saiu identica ao 27.2: o script preferiu o cache do 27.2 e reaproveitou o binario.
- Repetida com DSC_LOCAL do 23G83 e RUN_TMP proprio: binario correto criado, mas o Ghidra nao produziu o .c. Causa desconhecida, suspeita de nome mangled diferente no 26.6.1 (assinatura mudou) ou simbolo ausente.
- Criado atalho ~/Desktop/Crush Triage.command que sobe o proxy e abre o crush no repo.
- 23G83 decompilado com o nome mangled correto (sem o 6o parametro `PKS3_`, que so existe no 27.2). Ghidra headless, 154s, 310 linhas. Diff de 546 linhas e veredito de 208 linhas gravados em docs/findings/. Veredito: itens 4 e 7 herdados e nao corrigidos, item 3 regressao de robustez, itens 1 e 6 comportamento novo, itens 2 e 5 neutros.
- Premissa de AGENTS.md corrigida: o 6o argumento de mapSplitCacheSystemWide NAO e incompativel. O tipo e `SharedCacheLoadInfo const*`, o valor e o mesmo `loadInfo` que o preflight principal escreveu em +0x19 antes do laco de subcaches. Heranca coerente em tipo e valor.
- Condicao do filtro de auth GOT estava invertida nas notas e foi corrigida: o mapping so e descartado com o bit 7 ligado E o flag desligado; com o flag ligado ele e copiado e o throw dispara.
- Novo caso registrado: com `local_405c > 0` e todos os mappings com bit 7 ligado e flag desligado, nada e copiado e a linha 253 grava count == 0, com retorno de sucesso e CacheInfo vazio.
