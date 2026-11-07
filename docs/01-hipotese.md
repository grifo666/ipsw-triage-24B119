# Hipótese

> A validação de assinatura da dyld shared cache exige o `cdhash` de **cada**
> arquivo do cache no trust cache. O build 24B119 valida os subcaches um a um e
> aborta no primeiro `cdhash` ausente, com
> `code signature registration for shared cache failed`.

## Base

- `dyld/SharedCacheRuntime.cpp` chama `fcntl(F_ADDFILESIGS_RETURN)` uma vez por
  arquivo de cache, dentro de `preflightCacheFile()`, e aborta o carregamento
  inteiro se qualquer chamada falhar.
- O `cdhash` é calculado pelo kernel sobre o CodeDirectory inteiro, truncado em
  20 bytes (`xnu/bsd/kern/ubc_subr.c`).
- O trust cache é o primeiro passo do pipeline do AMFI; acerto dispensa
  criptografia e encerra a validação.

## Previsões testáveis

1. Com o `cdhash` do arquivo principal no trust cache, o erro muda de arquivo em
   vez de sumir.
2. Com os `cdhash` de todos os arquivos presentes, o carregamento passa da etapa
   de assinatura.
3. Um único arquivo com a região de assinatura zerada aborta o carregamento,
   mesmo com todos os outros cobertos.

## Falsificação

A hipótese cai se:

- o erro persistir no mesmo arquivo já presente no trust cache; ou
- o carregamento avançar sem os `cdhash` dos subcaches; ou
- a falha ocorrer em etapa posterior ao registro de assinatura (por exemplo
  `mmap` ou fixup), sem relação com `cdhash`.

## Não é a hipótese

Não se afirma que 24B119 tenha regredido em relação a 23G83. O diff serve para
verificar isso, não para pressupô-lo.
