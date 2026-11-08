# AGENTS.md — memória de sessão e handoff

Leia isto antes de qualquer coisa. É o estado acumulado do trabalho; não rederivar.

## Regras de trabalho

- O usuario tem ansiedade: antes de qualquer sequencia de comandos, listar os passos numerados (passo 1/N, 2/N...) e o que cada um busca. Dar estimativa de tempo quando o passo for demorado. Nunca emendar comandos sem avisar o plano.

- Falar com o usuario em linguagem simples, sem jargao. Termo tecnico so quando inevitavel, explicado na mesma frase.

- Shell é **zsh**, não bash. Gerenciador de pacotes é **MacPorts**, não brew.
- **Um prompt de shell por turno** (o usuário cola e devolve a saída).
- Sem emoji nas respostas.
- Prompts longos com JSON inline estavam sendo truncados pela interface: mandar payload em arquivo (`-d @/tmp/p.json`).
- O campo de pergunta do cliente às vezes renderiza como texto livre em vez de sim/não.
- Antes de `git push`: `git add` + `commit` primeiro, depois `git pull --rebase` (nunca rebase com árvore suja).

## Objetivo

Projeto de triagem estática do dyld shared cache do iOS **27.2 (24B119)** contra a base **26.6.1 (23G83)**, alvo iPhone18,2, para achar bug novo ou confirmar CVE em funções de preflight do cache. Faz parte de um produto estilo Pegasus/NSO; existe um GIST com o código.

Repo: `~/triage` = `grifo666/ipsw-triage-24B119`, branch `main`.

## Ambiente

- Disco interno ~90% cheio. O trabalho pesado vai para `/Volumes/WABACKUP` (sparse bundle **APFS**, montado com duplo clique; precisa estar montado).
- `ipsw diff` precisa de ~27G+ de temp. Alternativa aprovada e não feita: `diskutil apfs addVolume disk4 APFS TRIAGE -quota 80g` e rodar o diff lá.
- Artefato `binaries-24B119` do Actions expira em 21/11.
- `OPENAI_API_KEY` vazio → `ipsw --dec` falha rápido; a decompilação usa Ghidra.

## Armadilha já diagnosticada (não repetir)

`ipsw diff` ficou 1h23 em estado `UN`. Não era disco nem filesystem: spindump mostrou `wait4` no `aea` bloqueado por krwlock do `diskimagesiod`. Correção: matar `aea`, `ipsw` e `diskimagesiod`, e remontar o sparse bundle. O cache daquela execução era um DB vazio de 4KB — irrecuperável.

## Pipeline CI

`.github/workflows/extract.yml` com `gh workflow run`. Inputs corretos: `componente`, `device`, `build`, `target_symbol`, `target_symbols`, `dyld_path` (default `/usr/lib/dyld`).

Defeitos já corrigidos, todos verificados por run verde:

1. `-noanalysis` no analyzeHeadless matava a decompilação → trocado por `-analysisTimeoutPerFile 1800`.
2. `ghidra.log` não era publicado e o tombstone `nao-gerado.txt` era decidido por glob de diretório → por símbolo.
3. `params.env` sobrescrevia o env do workflow → atribuições viraram `${VAR-default}`.
4. Run em lote perdia tudo ao falhar no símbolo 12 → `git commit` por símbolo + `if: always()` no commit e no artifact.

`extract.sh` usa `ETAPA=disasm|decomp` e `TARGET_SYMBOL`. O step "instalar ghidra" fica cinza porque é pulado por `if: cache-hit != 'true'` — comportamento correto.

## Achados técnicos já estabelecidos

- `preflightCacheFile`: `mappingOffset` não é validado contra o buffer de 0x4000; flag herdada de `options+0x19`; caminho com `mappingCount == 1` chega em `std::bad_optional_access`. Candidato mais forte.
- `preflightSubCacheFile`: 5º argumento NULL para subcache, 6º argumento passthrough puro.
- `preflightMainCacheFile`: 6º argumento NULL e lógica de seleção `.development`.
- `mapSplitCacheSystemWide`: o loop passa `loadInfo` no 6º argumento (incompatível com `SharedCacheOptions*`) e vaza fds quando o subcache falha.
- Base: `validMagic`, `buildRootsBitmaps`, `DynamicRegion`, `hash_rank`, `mapSplitCachePrivate`, `loadDyldCache`.

## Pendências

- Triagem dos 16 `.c` concluída; veredito em `docs/findings/INDEX.md`. Bug real: `preflightCacheFile`, `mapSplitCacheSystemWide`, `mapSplitCachePrivate`. Provar no aparelho o header forjado de `preflightCacheFile` (count==1 + fileOffset!=0 + slide).
- Os tres simbolos que falharam foram recuperados e triados: `validSemanticsSegments`, `validStructureLoadCommands` (ambos com `__ZNK` no lugar do `__ZN` errado) e `lockdownDyldDataConst` (corpo inlineado; so o `_block_invoke` tem simbolo). Todos robustos. Proximo passo, se preciso: decompilar `handleDyldInCache` (tambem sem simbolo proprio) para a logica completa de lockdown.
- Template em `docs/findings/`, fila `SYMBOLS` no `params.env`, diff de decomp entre builds, script Ghidra enumerando funções dyld3.
- Achar o GIST do produto.
- Opcional: volume `TRIAGE` com quota e diff completo lá.

## Proxy Venice local (para rodar o agente fora da web)

- `~/venice-ai-chat-proxy`, fork `aintlikeu/venice-ai-chat-proxy`. Escuta em `127.0.0.1:3456`.
- Login: OAuth Google cria a conta (`wagnerstanko@gmail.com`); senha falha. Funciona com `VENICE_FIRST_FACTOR=email_code` (patch em `scripts/login-wreq.mjs`) e depois `--mfa-code`.
- Subir com `nohup node ./src/proxy.mjs > /tmp/venice-proxy.log 2>&1 & disown`. Matar por PID de `lsof -ti tcp:3456` — `pkill -f` não pega.
- Sem tier gratuito de API; DIEM ou x402 são os caminhos headless.
- **Patch do dialeto DSML** (o modelo responde `` com `｜` = U+FF5C, espaço após cada marcador e `calls` no lugar de `tool_call`): normalizador com retenção de marcador parcial no `push`, tag `<invoke>` aceita solta, formato `invoke` para `/deepseek/`, e o `"<$1tool_call"` precisa repor o `<`. Suíte `npm run check:tool-emulation` em 359/0.
- Modelo em uso: `deepseek-v4-1-flash-uncensored`.

## Harness

`crush` v0.100.0 em `~/.local/bin/crush` (**x86_64 — a máquina é Intel**). Config em `~/.config/crush/crushrc` com provider `venice-local` (`--type completions`, base `http://127.0.0.1:3456/v1`), modelo `venice-local/deepseek-v4-1-flash-uncensored`. Modo não interativo: `crush -y run "..."`.

## Current state (2026-11-07)

- HEAD 0db4c9b; triagem dos 16 `.c` concluida e indexada em `docs/findings/INDEX.md`.
- 16 `.c` presentes em `06-decomp/dyld/`, 16 findings, veredito em INDEX.md. Bug real: preflightCacheFile, mapSplitCacheSystemWide, mapSplitCachePrivate. Ponto fraco: trap de hash_rank, fd dos dois preflight.
- Unico simbolo ainda sem `.c`: `__ZN5dyld4L21lockdownDyldDataConstEPKN6mach_o12UnsafeHeaderE` (falhou na decomp). Redisparar so ele.
- Prova no aparelho pendente: header de cache forjado com mappingOffset grande (ou mappingWithSlideOffset) e count 1..8; caso count==1 com fileOffset!=0 + slide para o throw.
- Harness no ar: proxy em 127.0.0.1:3456, crush com provider venice-local, modelo deepseek-v4-1-flash-uncensored.
