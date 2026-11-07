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

`__ZN5dyld3L18preflightCacheFileERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoEPNS_9CacheInfoEiPNSt3__15arrayIA32_cLm128EEEPKS3_` — VA `0x18050a0f4`. Disassembly em `05-disasm/dyld/`; decompilação em `06-decomp/dyld/`.

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

- **Decompilação.** O ramo é `LLM → Ghidra headless → falha`. Sem `OPENAI_API_KEY` o backend `--dec` falha rápido; o backend Ghidra exige `analyzeHeadless` executável, derivado de `ANALYZE_HEADLESS`, de `GHIDRA_HOME` ou do `PATH`. Sem nenhum dos dois a etapa apaga `.c` e `.backend.txt`, registra aqui e o step fica vermelho sob `continue-on-error`.
- **Decompilação por LLM não exercitada.** O backend `--dec` nunca produziu saída: não há `OPENAI_API_KEY` no repositório nem nos secrets.
- **Sem verificação de endereço.** Nada confere que o decompilado corresponde à VA `0x18050a0f4` além do nome do símbolo.
- **Versões divergentes entre local e CI.** O artefato local saiu de Ghidra 12.2 e `ipsw` 3.1.741; o CI fixa Ghidra 12.0 e instala o `ipsw` corrente (3.1.743 no run 42400073162). 12.1+ não publica nativos macOS e `buildNatives` exigiria JDK 25 e Xcode.
- **`uuid` via JSON.** O UUID sai de `ipsw macho info --header`, não de `otool`. Se a CLI mudar o formato do JSON, o campo vira string vazia sem erro.
- **Falha não aborta o run.** Cada subcomando tem o código de saída capturado e vira um bullet aqui. O `INDEX.json` não tem campo `status`: o que denuncia falha é a lista de limitações.
- **Sem assinatura.** Nada é assinado nem verificado criptograficamente. O SHA-256 no índice detecta corrupção de transporte, não origem.
- **Escopo.** O diff é do IPSW inteiro; do relatório só o bloco do `dyld` é publicado e o restante é descartado.
- **Unidade de 120 KB.** Aplicada como 120 KiB = 122 880 bytes, valor idêntico ao de `split -b` e do `LIMIT` do `gen-index.sh`. Nenhum arquivo publicado passa disso.
- **Arquivo dividido.** Excedeu 120 KB: `04-symbols/all-symbols.txt`, publicado em partes `p0001` a `p0010`.
- **Diff incompleto por disco.** O volume SystemOS não montou: `no space left on device` em `/var/folders/...`. A seção MachOs é parcial e está truncada em `09-diff/machos-partial.p*.txt`. Kernel, DSC e dyld saíram completos.
- **Diff não roda no CI.** `BASE_IPSW` em `params.env` aponta para caminho local; no runner o passo é pulado e registrado aqui. O `09-diff` versionado veio de execução local.

## Como reproduzir

Edite `params.env` com `BUILD`, `DEVICE`, `IPSW_LOCAL` e `TARGET_SYMBOL`, depois:

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

Pela web: Actions → extract → Run workflow → informe `build` e `target_symbol`. O artifact sai como `binaries-24B119`.

## Baseline

O diff é contra `iPhone18,2_26.6.1_23G83_Restore.ipsw`. Sem a baseline o `extract.sh` ainda roda, mas o passo de diff é pulado e registrado nas Limitações.

## Critérios de aceite

- [x] Repositório público com a árvore da seção 3 na `main`
- [x] `INDEX.json` válido cobrindo 100% dos arquivos publicados (45 itens, `gen-index.sh` rc=0)
- [x] Nenhum arquivo acima de 120 KB; nenhum binário versionado
- [x] Workflow concluiu com sucesso na versao anterior, antes da divisao em etapas — run 42389703176
- [ ] Workflow na versao com etapas separadas — run pendente
- [x] Artifact `binaries-24B119` presente na versao anterior, retenção 14 dias (expira 2026-11-21)
- [x] README com todas as seções preenchidas
- [x] `docs/00-cve.md` com o advisory (sem identificador atribuído)
- [x] Artefatos legíveis em URL crua
## Registro de execução

Os bullets abaixo são anexados pelo `extract.sh` via `registrar_limite` e descrevem a execução que os produziu.

- arquivo dividido por exceder 120 KB: 04-symbols/all-symbols.txt
- diff pulado: BASE_IPSW nao fornecido
- decompilacao de `__ZN5dyld3L18preflightCacheFileERKNS_18SharedCacheOptionsEPNS_19SharedCacheLoadInfoEPNS_9CacheInfoEiPNSt3__15arrayIA32_cLm128EEEPKS3_` pulada: nenhum backend produziu saida (--dec exige OPENAI_API_KEY no ambiente, Ghidra exige GHIDRA_HOME ou ANALYZE_HEADLESS)
- `ipsw diff` falhou
- gen-index.sh falhou
