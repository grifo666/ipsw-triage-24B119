// @category triage
// Decompila uma funcao por simbolo e grava C em arquivo.
// Funciona com -noanalysis: desmonta e cria a funcao por conta propria.
import ghidra.app.decompiler.*;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import java.io.File;
import java.io.FileWriter;

public class DecompileSymbol extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] a = getScriptArgs();
        if (a.length < 2) {
            throw new IllegalArgumentException("uso: DecompileSymbol <simbolo> <arquivo_saida>");
        }
        String nome = a[0];
        String saida = a[1];

        Address addr = null;
        SymbolIterator it = currentProgram.getSymbolTable().getSymbols(nome);
        while (it.hasNext()) {
            Symbol s = it.next();
            if (s.getAddress().isMemoryAddress()) { addr = s.getAddress(); break; }
        }
        if (addr == null) throw new IllegalStateException("simbolo ausente: " + nome);

        Function alvo = currentProgram.getFunctionManager().getFunctionAt(addr);
        if (alvo == null) {
            if (getInstructionAt(addr) == null) disassemble(addr);
            alvo = createFunction(addr, nome);
            if (alvo == null) {
                throw new IllegalStateException("nao foi possivel criar funcao em " + addr);
            }
        }

        DecompInterface dec = new DecompInterface();
        dec.toggleCCode(true);
        dec.toggleSyntaxTree(true);
        dec.openProgram(currentProgram);
        try {
            DecompileResults r = dec.decompileFunction(alvo, 120, monitor);
            if (r == null || !r.decompileCompleted()) {
                throw new IllegalStateException("falha na decompilacao: " + nome);
            }
            try (FileWriter w = new FileWriter(new File(saida))) {
                w.write(r.getDecompiledFunction().getC());
            }
        } finally {
            dec.dispose();
        }
    }
}
