# CVE e advisory

- **CVE:** triagem aberta (nenhum identificador atribuído)
- **Advisory:** sem advisory
- **Componente:** dyld — `dyld shared cache`
- **Device:** iPhone18,2
- **Build alvo:** 24B119
- **Build de baseline:** 23G83

## Contexto

Triagem aberta, sem CVE. O alvo é a validação de assinatura da dyld shared cache:
o AMFI valida cada arquivo do cache (`dyld_shared_cache_arm64e` e cada
`dyld_shared_cache_arm64e.NN`) pelo `cdhash` do seu CodeDirectory, antes de
qualquer veredito de política.

Ordem do pipeline, conforme o código público do XNU e do dyld:

1. `dyld` chama `fcntl(F_ADDFILESIGS_RETURN)` por arquivo, com
   `fs_blob_start = codeSignatureOffset` do header do próprio cache.
2. O kernel parseia o SuperBlob, escolhe o CodeDirectory de maior `hash_rank` e
   calcula o `cdhash` (hash do CD, truncado em 20 bytes).
3. O AMFI consulta o trust cache por esse `cdhash`. Acerto encerra a validação
   como *platform binary*, sem criptografia.
4. Sem acerto, o CoreTrust classifica o assinante. Assinatura adhoc recebe
   política 0, que não é aceita em iOS.
5. Só então o `amfid` é consultado, por porta Mach.

## Por que isso importa

Um cache cujo `cdhash` não está no trust cache não carrega, e o `dyld` aborta
com `code signature registration for shared cache failed`. Como cada arquivo do
cache é validado isoladamente, cobrir o arquivo principal não basta: é preciso
cobrir todos os subcaches.

## O que não se sabe

- Qual CVE, se houver, corresponde a este comportamento.
- Se o build 24B119 alterou a ordem ou os gates do pipeline em relação ao 23G83.
