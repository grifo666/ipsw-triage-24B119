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
