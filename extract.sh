#!/bin/bash
# Triagem estatica de IPSW. Gera apenas texto; binarios ficam em RUN_TMP.
set -euo pipefail

export TERM=dumb
export NO_COLOR=1

strip_ansi() { sed -r 's/\x1b\[[0-9;]*[mGKHF]//g'; }

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

# shellcheck disable=SC1091
[ -f params.env ] && . ./params.env

: "${COMPONENTE:?defina COMPONENTE em params.env}"
: "${DEVICE:?defina DEVICE em params.env}"
: "${BUILD:?defina BUILD em params.env}"

ETAPA="${ETAPA:-all}"
case "$ETAPA" in all|disasm|decomp) ;; *) echo "ERRO: ETAPA invalida: $ETAPA" >&2; exit 1 ;; esac
DEC_FALHOU=0

RUN_TMP="${RUN_TMP:-$ROOT/_tmp}"
mkdir -p "$RUN_TMP"
mkdir -p 01-info 03-entitlements 04-symbols 07-strings 08-kernel 09-diff
LIMIT=122880   # 120 KiB

LIMITES="$ROOT/README.md"

registrar_limite() {
  local msg="$1"
  grep -Fqx -- "- $msg" "$LIMITES" || printf -- "- %s\n" "$msg" >> "$LIMITES"
}

dividir() {
  local f="$1"
  local sz
  sz=$(wc -c < "$f")
  if [ "$sz" -le "$LIMIT" ]; then return 0; fi
  local base="${f%.txt}" n=1 part
  rm -f "${base}".p[0-9]*
  split -b "$LIMIT" -d -a 4 "$f" "${base}.p"
  rm -f "$f"
  for part in "${base}".p[0-9][0-9][0-9][0-9]; do
    mv "$part" "${base}.p$(printf '%04d' "$n").txt"
    n=$((n+1))
  done
  registrar_limite "arquivo dividido por exceder 120 KB: $f"
}

[ -x "${IPSW_BIN:-}" ] || IPSW_BIN="$(command -v ipsw || true)"
if [ -z "$IPSW_BIN" ]; then
  if command -v brew >/dev/null 2>&1; then
    brew install blacktop/tap/ipsw
    IPSW_BIN="$(command -v ipsw)"
  else
    echo "ERRO: ipsw nao encontrado no PATH e brew indisponivel; defina IPSW_BIN em params.env" >&2
    exit 1
  fi
fi

"$IPSW_BIN" version 2>&1 | strip_ansi > 01-info/ipsw-version.txt || true

for sub in macho dyld kernel; do
  "$IPSW_BIN" "$sub" --help 2>&1 | strip_ansi > "01-info/ipsw-help-$sub.txt" || \
    registrar_limite "\`ipsw $sub --help\` falhou"
done

IPSW="${IPSW:-}"

if [ -z "$IPSW" ]; then
  IPSW="$(find "$RUN_TMP" -maxdepth 2 -name '*.ipsw' 2>/dev/null | head -1)"
fi
if [ -z "$IPSW" ]; then
  if [ -n "${IPSW_LOCAL:-}" ] && [ -f "$IPSW_LOCAL" ]; then
    IPSW="$IPSW_LOCAL"
  elif [ -n "${IPSW_URL:-}" ]; then
    IPSW="$RUN_TMP/firmware.ipsw"
    curl -L --fail -o "$IPSW" "$IPSW_URL"
  else
    "$IPSW_BIN" download ipsw --device "$DEVICE" --build "$BUILD" \
      --output "$RUN_TMP" --confirm 2>&1 | strip_ansi | tail -5
    IPSW="$(find "$RUN_TMP" -maxdepth 2 -name "*.ipsw" | head -1)"
  fi
fi
[ -f "$IPSW" ] || { echo "ERRO: IPSW nao encontrado" >&2; exit 1; }
echo "IPSW: $IPSW"

shasum -a 256 "$IPSW" > 01-info/ipsw-sha256.txt
"$IPSW_BIN" info "$IPSW" 2>&1 | strip_ansi > 01-info/ipsw-info.txt || \
  registrar_limite "\`ipsw info\` falhou no build $BUILD"
dividir 01-info/ipsw-info.txt

CACHE_DIR=""
BIN=""
MACHO_DIR=""

preparar_dyld() {
  local prev="$RUN_TMP/bin/$(basename "$DYLD_PATH")"
  if [ -f "$prev" ] && [ -s "$prev" ]; then
    BIN="$prev"
    echo "BIN reaproveitado: $BIN"
    return 0
  fi

  CACHE_DIR="${CACHE_DIR:-}"
  if [ -z "$CACHE_DIR" ] && [ -n "${DSC_LOCAL:-}" ] && [ -d "$DSC_LOCAL" ]; then
    CACHE_DIR="$DSC_LOCAL"
  fi
  if [ -z "$CACHE_DIR" ]; then
    "$IPSW_BIN" extract --dyld --dyld-arch arm64e --output "$RUN_TMP/dsc" \
      "$IPSW" 2>&1 | strip_ansi | tail -5
    CACHE_DIR="$(find "$RUN_TMP" -maxdepth 3 -name 'dyld_shared_cache_arm64e*' \
      -not -name '*.symbols' -not -name '*.atlas' | head -1)"
    CACHE_DIR="$(dirname "$CACHE_DIR")"
  fi
  [ -d "$CACHE_DIR" ] || { echo "ERRO: cache nao encontrado" >&2; exit 1; }
  echo "CACHE: $CACHE_DIR"

  "$IPSW_BIN" dyld info "$CACHE_DIR/dyld_shared_cache_arm64e" 2>&1 | strip_ansi \
    > 01-info/dsc-info.txt || registrar_limite "\`ipsw dyld info\` falhou"

  BIN="$RUN_TMP/bin/target"
  mkdir -p "$RUN_TMP/bin"
  "$IPSW_BIN" dyld extract "$CACHE_DIR/dyld_shared_cache_arm64e" "$DYLD_PATH" \
    --output "$RUN_TMP/bin" 2>&1 | strip_ansi | tail -5 || \
    { echo "ERRO: extracao de $DYLD_PATH falhou" >&2; exit 1; }
  BIN="$(find "$RUN_TMP/bin" -type f -name "$(basename "$DYLD_PATH")" | head -1)"
  [ -f "$BIN" ] || { echo "ERRO: binario alvo nao extraido" >&2; exit 1; }
}

preparar_kernel() {
  "$IPSW_BIN" extract --kernel --output "$RUN_TMP/kc" "$IPSW" 2>&1 | strip_ansi | tail -5
  local kc
  kc="$(find "$RUN_TMP/kc" -maxdepth 3 -name 'kernelcache*' | head -1)"
  [ -f "$kc" ] || { echo "ERRO: kernelcache nao extraido" >&2; exit 1; }

  "$IPSW_BIN" kernel version "$kc" 2>&1 | strip_ansi > 08-kernel/kernel-info.txt || \
    registrar_limite "\`ipsw kernel version\` falhou"
  "$IPSW_BIN" kernel kexts "$kc" 2>&1 | strip_ansi > 08-kernel/kexts.txt || \
    registrar_limite "\`ipsw kernel kexts\` falhou"
  dividir 08-kernel/kexts.txt
  "$IPSW_BIN" kernel symbolsets "$kc" 2>&1 | strip_ansi \
    > 08-kernel/kernel-symbols.txt || \
    registrar_limite "\`ipsw kernel symbolsets\` falhou"
  dividir 08-kernel/kernel-symbols.txt

  if [ -n "${KEXT_BUNDLE_ID:-}" ]; then
    "$IPSW_BIN" kernel extract "$kc" "$KEXT_BUNDLE_ID" -o "$RUN_TMP/kexts" \
      2>&1 | strip_ansi | tail -5
    BIN="$(find "$RUN_TMP/kexts" -type f -name "$KEXT_BUNDLE_ID" | head -1)"
  else
    BIN="$kc"
  fi
}

case "$COMPONENTE" in
  dyld)   preparar_dyld ;;
  kernel) preparar_kernel ;;
  *) echo "ERRO: COMPONENTE invalido: $COMPONENTE" >&2; exit 1 ;;
esac
echo "BIN: $BIN"

MACHO_DIR="02-macho/$(basename "$BIN")"
mkdir -p "$MACHO_DIR" 04-symbols 05-disasm/$(basename "$BIN") \
  09-diff   06-decomp/$(basename "$BIN") 07-strings 03-entitlements

"$IPSW_BIN" macho info --arch arm64e --header "$BIN" 2>&1 | strip_ansi \
  > "$MACHO_DIR/header.txt" || registrar_limite "\`macho info --header\` falhou"

"$IPSW_BIN" macho info --arch arm64e --loads "$BIN" 2>&1 | strip_ansi \
  > "$MACHO_DIR/loadcmds.txt" || registrar_limite "\`macho info --loads\` falhou"

grep -E 'LC_LOAD_(WEAK_)?DYLIB|LC_REEXPORT_DYLIB' "$MACHO_DIR/loadcmds.txt" 2>/dev/null \
  | sed -E 's/.*name[[:space:]]*//' | sort -u > "$MACHO_DIR/libraries.txt" || true
[ -s "$MACHO_DIR/libraries.txt" ] || echo "nenhuma dylib referenciada" \
  > "$MACHO_DIR/libraries.txt"
dividir "$MACHO_DIR/loadcmds.txt"

if [ ! -s "$MACHO_DIR/uuid.txt" ]; then
  "$IPSW_BIN" macho info --arch arm64e --json "$BIN" 2>/dev/null \
    | grep -o '"uuid":[^,]*' | head -1 > "$MACHO_DIR/uuid.txt" || true
fi
[ -s "$MACHO_DIR/uuid.txt" ] || echo "uuid nao extraido" > "$MACHO_DIR/uuid.txt"

"$IPSW_BIN" macho info --arch arm64e --ent "$BIN" 2>&1 | strip_ansi \
  > 03-entitlements/entitlements.plist || \
  registrar_limite "\`macho info --ent\` falhou"
  dividir 03-entitlements/entitlements.plist
"$IPSW_BIN" macho info --arch arm64e --ent-der "$BIN" 2>&1 | strip_ansi \
  > 03-entitlements/entitlements-der.txt || true

if command -v nm >/dev/null 2>&1; then
  nm -nm "$BIN" 2>&1 | strip_ansi > 04-symbols/all-symbols.txt || \
    registrar_limite "\`nm -nm\` falhou"
  nm -gU "$BIN" 2>&1 | strip_ansi > 04-symbols/exports.txt || \
    registrar_limite "\`nm -gU\` falhou"
  nm -u "$BIN" 2>&1 | strip_ansi > 04-symbols/imports.txt || \
    registrar_limite "\`nm -u\` falhou"
  dividir 04-symbols/exports.txt
  dividir 04-symbols/imports.txt
[ -s 04-symbols/imports.txt ] || echo "nenhum simbolo importado reportado por nm -u" > 04-symbols/imports.txt
else
  registrar_limite "nm indisponivel; 04-symbols ficou vazio"
fi
"$IPSW_BIN" macho info --arch arm64e --symbols "$BIN" 2>&1 | strip_ansi \
  >> 04-symbols/all-symbols.txt || true
dividir 04-symbols/all-symbols.txt

strings -a -n 6 "$BIN" 2>/dev/null | sort -u | strip_ansi > 07-strings/strings-filtradas.txt
dividir 07-strings/strings-filtradas.txt

SIMBOLO="${TARGET_SYMBOL:-}"
if [ -n "$SIMBOLO" ] && [ "$SIMBOLO" != "indefinido" ]; then
  if [ "$ETAPA" != "decomp" ]; then
  ALVO_DIS="05-disasm/$(basename "$BIN")/$SIMBOLO.txt"
  if "$IPSW_BIN" macho disass --arch arm64e --symbol "$SIMBOLO" "$BIN" 2>&1 \
       | strip_ansi > "$ALVO_DIS" && [ -s "$ALVO_DIS" ]; then
    dividir "$ALVO_DIS"
  else
    rm -f "$ALVO_DIS"
    registrar_limite "disassembly de \`$SIMBOLO\` falhou"
  fi

  fi
  if [ "$ETAPA" != "disasm" ]; then
  ALVO_DEC="06-decomp/$(basename "$BIN")/$SIMBOLO.c"
  DEC_OK=0
  DEC_BACKEND=""
  # zera saida e lapide de tentativa anterior antes de reescrever
  rm -f "$ALVO_DEC" "${ALVO_DEC%.c}.backend.txt"

  GHIDRA_HEADLESS="${ANALYZE_HEADLESS:-}"
  if [ -z "$GHIDRA_HEADLESS" ] && [ -n "${GHIDRA_HOME:-}" ]; then
    GHIDRA_HEADLESS="$GHIDRA_HOME/support/analyzeHeadless"
  fi
  if [ -z "$GHIDRA_HEADLESS" ]; then
    GHIDRA_HEADLESS="$(command -v analyzeHeadless 2>/dev/null || true)"
  fi
  if [ -n "$GHIDRA_HEADLESS" ] && [ ! -x "$GHIDRA_HEADLESS" ]; then
    echo "AVISO: analyzeHeadless nao executavel: $GHIDRA_HEADLESS" >&2
    GHIDRA_HEADLESS=""
  fi
  if [ -n "${GHIDRA_JAVA_HOME:-}" ] && [ ! -d "$GHIDRA_JAVA_HOME" ]; then
    echo "AVISO: GHIDRA_JAVA_HOME inexistente, usando JAVA_HOME do ambiente: $GHIDRA_JAVA_HOME" >&2
    GHIDRA_JAVA_HOME=""
  fi

  # backend 1: ipsw --dec (LLM; sem OPENAI_API_KEY falha rapido e cai no proximo)
  if "$IPSW_BIN" macho disass --arch arm64e --symbol "$SIMBOLO" --dec \
       --dec-lang C "$BIN" 2>&1 | strip_ansi > "$ALVO_DEC" && [ -s "$ALVO_DEC" ]; then
    DEC_OK=1
    DEC_BACKEND="ipsw --dec"
  else
    rm -f "$ALVO_DEC"
  fi

  # backend 2: Ghidra headless
  if [ "$DEC_OK" -eq 0 ] && [ -x "${GHIDRA_HEADLESS:-/nonexistent}" ]; then
    mkdir -p "$RUN_TMP/ghidra"
    if JAVA_HOME="${GHIDRA_JAVA_HOME:-${JAVA_HOME:-}}" "$GHIDRA_HEADLESS" \
         "$RUN_TMP/ghidra" triage -import "$BIN" \
         -scriptPath "$ROOT/ghidra_scripts" \
         -postScript DecompileSymbol.java "$SIMBOLO" "$ALVO_DEC" \
         -analysisTimeoutPerFile 1800 -deleteProject \
         2>&1 | strip_ansi > "${ALVO_DEC%.c}.ghidra.log" && [ -s "$ALVO_DEC" ]; then
      DEC_OK=1
      DEC_BACKEND="ghidra-headless"
      dividir "${ALVO_DEC%.c}.ghidra.log" 2>/dev/null || true
    else
      rm -f "$ALVO_DEC"
    fi
  fi

  if [ "$DEC_OK" -eq 1 ]; then
    printf 'backend: %s\n' "$DEC_BACKEND" > "${ALVO_DEC%.c}.backend.txt"
    dividir "$ALVO_DEC"
  else
    rm -f "$ALVO_DEC" "${ALVO_DEC%.c}.backend.txt"
    DEC_FALHOU=1
    echo "ERRO: decompilacao de $SIMBOLO nao produzida por nenhum backend" >&2
    registrar_limite "decompilacao de \`$SIMBOLO\` pulada: nenhum backend produziu saida (--dec exige OPENAI_API_KEY no ambiente, Ghidra exige GHIDRA_HOME ou ANALYZE_HEADLESS)"
  fi
  fi
else
  registrar_limite "TARGET_SYMBOL indefinido; 05-disasm e 06-decomp vazios"
fi

if [ -n "${BASELINE_BUILD:-}" ] && [ -n "${BASE_IPSW:-}" ] && [ -f "${BASE_IPSW:-}" ]; then
  # ipsw diff extrai GBs em $TMPDIR e grava cache SQLite em ~/Library/Caches/ipsw.
  # Ambos vao para DIFF_TMP, fora de $RUN_TMP (que pode estar no disco interno).
  DIFF_TMP="${DIFF_TMP:-$RUN_TMP/diff-tmp}"
  DIFF_MIN_GIB="${DIFF_MIN_GIB:-20}"
  mkdir -p "$DIFF_TMP/cache"
  LIVRE_GIB="$(df -g "$DIFF_TMP" | awk 'NR==2 {print $4}')"
  DIFF_RAW="$RUN_TMP/diff-${BASELINE_BUILD}-${BUILD}.txt"
  if [ "${LIVRE_GIB:-0}" -lt "$DIFF_MIN_GIB" ]; then
    registrar_limite "\`ipsw diff\` pulado: $DIFF_TMP tem ${LIVRE_GIB}GiB, minimo ${DIFF_MIN_GIB}GiB"
  elif TMPDIR="$DIFF_TMP" "$IPSW_BIN" diff --cache-dir "$DIFF_TMP/cache" \
       "$BASE_IPSW" "$IPSW" 2>&1 | strip_ansi > "$DIFF_RAW"; then
    head -310 "$DIFF_RAW" > "09-diff/summary.md"
    awk '/^## DSC$/{d=1} d && /^#### /{exit} d' "$DIFF_RAW" >> "09-diff/summary.md"
    awk '/^##### `/ { b = ($0 == "##### `dyld`") } b' "$DIFF_RAW" \
      > "09-diff/dyld-${BASELINE_BUILD}-${BUILD}.txt"
    rm -f "$DIFF_RAW"
    dividir "09-diff/summary.md"
    dividir "09-diff/dyld-${BASELINE_BUILD}-${BUILD}.txt"
  else
    rm -f "$DIFF_RAW"
    registrar_limite "\`ipsw diff\` falhou"
  fi
else
  registrar_limite "diff pulado: BASE_IPSW nao fornecido"
fi

# secoes que nao podem ficar vazias
DECOMP_DIR="06-decomp/$(basename "$BIN")"
if [ -n "${TARGET_SYMBOL:-}" ] && [ "$TARGET_SYMBOL" != "indefinido" ]; then
  if [ -f "$DECOMP_DIR/$TARGET_SYMBOL.c" ]; then
    rm -f "$DECOMP_DIR/nao-gerado.txt"
  else
    echo "decompilacao nao gerada para $TARGET_SYMBOL: ver Limitacoes" > "$DECOMP_DIR/nao-gerado.txt"
  fi
elif compgen -G "$DECOMP_DIR/*.c" >/dev/null; then
  rm -f "$DECOMP_DIR/nao-gerado.txt"
else
  echo "decompilacao nao gerada: ver Limitacoes" > "$DECOMP_DIR/nao-gerado.txt"
fi
[ -s 08-kernel/kexts.txt ] || echo "componente $COMPONENTE nao usa kernel" \
  > 08-kernel/kexts.txt
[ -s 08-kernel/kernel-info.txt ] || echo "componente $COMPONENTE nao usa kernel" \
  > 08-kernel/kernel-info.txt
[ -s 08-kernel/kernel-symbols.txt ] || echo "componente $COMPONENTE nao usa kernel" \
  > 08-kernel/kernel-symbols.txt
[ -s 03-entitlements/sandbox-profile.txt ] || \
  echo "sem perfil de sandbox embutido" > 03-entitlements/sandbox-profile.txt
[ -s 09-diff/diff-${BASELINE_BUILD}-${BUILD}.txt ] || true

./gen-index.sh || { registrar_limite "gen-index.sh falhou"; exit 1; }
echo "FIM"
if [ "$ETAPA" = "decomp" ] && [ "$DEC_FALHOU" -eq 1 ]; then
  echo "ERRO: etapa decomp nao gerou decompilacao; step marcado como falho" >&2
  exit 1
fi
