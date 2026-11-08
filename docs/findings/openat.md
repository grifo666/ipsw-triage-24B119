# openat (wrapper)

- Simbolo: `__ZN5dyld3L6openatEiPKc.c` (19 linhas), Ghidra headless
- Classificacao: **robusto; wrapper de retry**

## Comportamento

Loop de retry em `_openat` que so repete em `EAGAIN` (0x23) e `EINTR` (4):

```
21:  do {
22:    uVar1 = _openat(param_1,param_2,0);
23:    if ((int)uVar1 != -1) return uVar1;
25:    piVar2 = ___error();
26:  } while ((*piVar2 == 0x23) || (piVar2 = ___error(), *piVar2 == 4));
27:  return 0xffffffff;
```

## Observacao

O loop nao tem teto de iteracoes: se `openat` retornar `EAGAIN`/`EINTR` perpetuamente (fds todos em EAGAIN sob contencao extrema), gira ate sucesso ou erro diferente. Na pratica EAGAIN/ EINTR sao transitorios e terminam; um EAGAIN persistente viraria busy-loop, mas sem custo de memoria. Nao e defeito, e decisao consciente de robustez contra sinais e contencao de fd.

## Classificacao final

- Sem defeito. Retry correto e restrito aos errnos transitorios.

