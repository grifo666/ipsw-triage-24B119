# forEachCDHashOfCodeSignature

- Simbolo: `__ZNK6mach_o5Image28forEachCDHashOfCodeSignatureEU13block_pointerFvNSt3__14spanIKhLm20EEEE.c` (26 linhas), Ghidra headless
- Classificacao: **stub de encaminhamento; sem defeito proprio**

## Comportamento

Chama `codeSignature()` para obter a assinatura; se ausente (`local_28 != 1`) retorna sem chamar o bloco; senao delega ao overload real `forEachCDHashOfCodeSignature(this, ..., param_1)` repassando a assinatura e o bloco.

```
codeSignature();
if (local_28 != '\x01') return;
SoftwareBreakpoint(0xc471) se ...
forEachCDHashOfCodeSignature(this, local_38, uStack_30, param_1);
```

## Observacao

As guardas `SoftwareBreakpoint(0xc471)` sao traps de consistencia (truque de `PAC`/assinatura nao resolvido pelo decompilador). A funcao nao tem logica de parsing; o trabalho (varrer os CDHashes e chamar o bloco com cada span de 20 bytes) esta no overload interno nao decompilado. Retorna cedo quando nao ha assinatura, evitando iterar sobre nada.

## Classificacao final

- Sem defeito. Encaminhamento condicionado a existencia de assinatura; logica real no overload interno.

