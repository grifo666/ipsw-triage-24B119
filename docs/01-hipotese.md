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

## Evidência de disassembly: portões de entrada

O bloco de entrada de `preflightCacheFile` (`0x18050a154`) é uma cadeia de validações
estruturais, cada uma com saída própria:

| Endereço | Instrução | Papel |
|---|---|---|
| `0x18050a164` | `cbz w0, loc_18050a174` | desvia de campo zero antes de qualquer comparação |
| `0x18050a1b0` | `cmp x0, #0x4, lsl #0xc` | compara tamanho com `0x4000` |
| `0x18050a1b4` | `b.ne loc_18050a1e8` | primeiro portão de rejeição |
| `0x18050a1c4` | `tbz w0, #0, loc_18050a1f4` | testa bit 0 de campo do header |
| `0x18050a1d4` | `cmp w8, w0` / `b.ne loc_18050a200` | igualdade entre dois campos |
| `0x18050a1e0` | `tbz w8, #0x1, loc_18050a210` | testa bit 1 |
| `0x18050a27c` | `retab` | saída antecipada |

Não há `bl` antes de `0x18050a418` (`bl _memcmp`), e `memcmp` compara conteúdo, não
assinatura. O `fcntl(F_ADDFILESIGS_RETURN)` previsto na hipótese não aparece nesse
trecho: fica adiante e ainda precisa ser localizado.

Ponto de desvio mais barato para teste: `0x18050a1b4`. Inverter a condição mantém a
execução no caminho que segue para `0x18050a1c4` em vez de saltar para `0x18050a1e8`.
