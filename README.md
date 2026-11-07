# ipsw-triage-24B119

Triagem estática de firmware. Só texto entra no git; binários vão como artifact.

## Objetivo

Extrair de um IPSW apenas artefatos em texto suficientes para análise estática,
consumíveis por um modelo de linguagem que lê URL crua e não executa nada.

## CVE e advisory

- CVE: triagem aberta (sem identificador)
- Advisory: sem advisory
- Detalhes: [docs/00-cve.md](docs/00-cve.md)

## Componente

`dyld` — validação de assinatura da dyld shared cache.

## Build e device

- Device: `iPhone18,2`
- Build alvo: `24B119`
- Baseline do diff: `23G83`

## Símbolo alvo

`indefinido` — `05-disasm` e `06-decomp` ficam vazios até um símbolo ser definido.

## Hipótese

[docs/01-hipotese.md](docs/01-hipotese.md)

## Status

aberto

## Mapa de artefatos

| Caminho | Papel |
|---------|-------|
| `params.env` | Fonte única de verdade: build, device, URL do IPSW, símbolo alvo. Todo script faz `source` nele. |
| `extract.sh` | Extrai o IPSW, isola o componente, coleta o binário e as strings, gera o diff contra a baseline. |
| `gen-index.sh` | Varre a árvore e produz `INDEX.json` (limite 120 KB) com metadados e SHA-256 dos artefatos. |
| `ghidra_scripts/DecompileSymbol.java` | Post-script headless do Ghidra: resolve o símbolo por nome e descompila a função. |
| `.github/workflows/extract.yml` | Orquestra no runner macOS via `workflow_dispatch`, sobe o artifact `binaries-<build>` com retenção de 14 dias. |
| `docs/00-cve.md` | Ficha do CVE e mapeamento para o componente. |
| `docs/01-hipotese.md` | Hipótese falsificável e critério de refutação. |
| `_tmp/` | Área de trabalho da extração: binário alvo e cache do diff. Não versionada. |
| IPSW | Baixado para `_tmp/` e apagado ao fim. Nunca versionado. |

## Limitações

- **Decompilação.** O ramo é `LLM → Ghidra headless → pulo`. Sem `analyzeHeadless` no `PATH`, o passo é marcado como pulo e o `INDEX.json` grava `decompiled: false`. Nada verifica que o decompilado corresponde ao endereço esperado além do nome do símbolo.
- **Ramo Ghidra nunca executado.** Ghidra não está instalado na máquina do operador. O script Java foi escrito e revisado, mas nunca rodou. A primeira execução é material não validado.
- **`uuid` via JSON.** O UUID sai de `ipsw macho info --header`, não de `otool`. Se a CLI mudar o formato do JSON, o campo vira string vazia sem erro.
- **Falha não aborta o run.** Cada subcomando roda com o código de saída capturado. Um passo quebrado não derruba o workflow: aparece no `INDEX.json` com `status: failed`. É intencional para triagem e é por isso que o verde do workflow não substitui a leitura do índice.
- **Sem assinatura.** Nada é assinado nem verificado criptograficamente. O SHA-256 no índice detecta corrupção de transporte, não origem.
- **Escopo.** O diff é do IPSW inteiro; do relatório só o bloco do `dyld` é publicado e o restante é descartado.
- **Decompilacao pulada.** sem OPENAI_API_KEY e sem analyzeHeadless.
- **Arquivo dividido.** Excedeu 120 KB: `04-symbols/all-symbols.txt`.
- **Diff incompleto por disco.** O volume SystemOS não montou: `no space left on device` em `/var/folders/...`. A seção MachOs do relatório é parcial e está publicada truncada em `09-diff/machos-partial.p*.txt`. Kernel, DSC e dyld saíram completos.
- **Decompilação não gerada nesta build.** `06-decomp/dyld/nao-gerado.txt` registra o pulo.

## Como reproduzir

Edite `params.env` com `BUILD`, `DEVICE`, `IPSW_URL` e `SYMBOL`, depois:

~~~sh
git clone https://github.com/grifo666/ipsw-triage-24B119
cd ipsw-triage-24B119
./extract.sh
./gen-index.sh
~~~

Com o IPSW já em disco, sem rede:

~~~sh
IPSW_LOCAL=/Volumes/XcodeBuild/ipsw/iPhone18,2_27.2_24B119_Restore.ipsw ./extract.sh
~~~

Pela web: Actions → extract → Run workflow → informe `build` e `symbol`. O artifact sai como `binaries-24B119`.

## Baseline

O diff é contra `iPhone18,2_26.6.1_23G83_Restore.ipsw`. Sem a baseline o `extract.sh` ainda roda, mas o passo de diff é pulado e registrado como `skipped`.
- arquivo dividido por exceder 120 KB: 04-symbols/all-symbols.txt
- decompilacao pulada: sem OPENAI_API_KEY e sem analyzeHeadless
- diff pulado: BASE_IPSW nao fornecido
