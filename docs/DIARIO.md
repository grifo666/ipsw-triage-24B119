# Diario de sessao

Append-only. Uma entrada por passo, com hora. O que foi tentado, o que funcionou, o que foi descartado e por que. Commitar a cada entrada: e isto que faz a memoria sobreviver.

## 2026-11-07
- Push por simbolo quebrado: o push estava dentro do else de "nada a commitar". Movido para dentro do laco. 40a76e3.
- Workflow rejeitado por chave YAML duplicada (permissions). Bloco velho removido.
- Batch de 15 simbolos redisparado com o push corrigido; os 15 chegaram em origin.
- Triagem dos 16 .c concluida, 19 findings escritos.
- Premissa corrigida: mappingCount aceita 1..8, rejeita 0 e >=9. CacheInfo 0x1c0, array de 8 slots, sem transbordo.
- Premissa corrigida: o throw exige fileOffset==0, nao !=0; o laco esta sob o teste de string de erro.
- Achados reais mantidos: offset sem validacao, throw alcancavel, vazamento de fd nos dois mappers.
- Regras novas: linguagem simples, passos numerados, execucao ao vivo sem tail.

## 2026-11-08
- Decompilacao do 26.6.1 saiu identica ao 27.2: o script preferiu o cache do 27.2 e reaproveitou o binario. Corrigido com cache e temporario por build.
