// @category triage
// Decompila uma funcao por simbolo e grava C em arquivo.
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import java.io.FileWriter;

public class DecompileSymbol extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] a = getScriptArgs();
        if (a.length < 2) {
            printerr("uso: DecompileSymbol <simbolo> <arquivo_saida>");
            return;
        }
        String nome = a[0];
        String saida = a[1];

        SymbolIterator it = currentProgram.getSymbolTable().getAllSymbols(true);
        Function alvo = null;
        while (it.hasNext()) {
            Symbol s = it.next();
            if (!s.getName().equals(nome)) continue;
            alvo = currentProgram.getFunctionManager().getFunctionAt(s.getAddress());
            if (alvo != null) break;
        }
        if (alvo == null) {
            printerr("simbolo sem funcao: " + nome);
            return;
        }

        DecompInterface dec = new DecompInterface();
        dec.openProgram(currentProgram);
        DecompileResults r = dec.decompileFunction(alvo, 60, monitor);
        try (FileWriter w = new FileWriter(saida)) {
            if (r != null && r.decompileCompleted()) {
                w.write(r.getDecompiledFunction().getC());
            } else {
                w.write("// falha na decompilacao: " + nome + "\n");
            }
        }
        dec.dispose();
    }
}
