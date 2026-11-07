#!/bin/bash
# Gera INDEX.json cobrindo todos os arquivos publicados. Falha acima de 120 KB.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

LIMIT=122880
OUT="INDEX.json"
TMP="$(mktemp)"

tipo_de() {
  case "$1" in
    01-info/*)           echo info ;;
    02-macho/*)          echo macho ;;
    03-entitlements/*)   echo entitlements ;;
    04-symbols/*)        echo symbols ;;
    05-disasm/*)         echo disasm ;;
    06-decomp/*)         echo decomp ;;
    07-strings/*)        echo strings ;;
    08-kernel/*)         echo kernel ;;
    09-diff/*)           echo diff ;;
    *)                   echo "info" ;;
  esac
}

simbolo_de() {
  case "$1" in
    05-disasm/*|06-decomp/*)
      local b
      b="$(basename "$1")"
      echo "${b%.*}"
      ;;
    *) echo "" ;;
  esac
}

proposito_de() {
  case "$1" in
    01-info/*)                     echo "metadados de firmware e da ferramenta" ;;
    02-macho/*/header.txt)         echo "cabecalho Mach-O" ;;
    02-macho/*/loadcmds.txt)       echo "load commands" ;;
    02-macho/*/libraries.txt)      echo "dylibs referenciadas" ;;
    02-macho/*/uuid.txt)           echo "uuid do binario" ;;
    03-entitlements/*)             echo "entitlements assinados" ;;
    04-symbols/*)                  echo "tabela de simbolos" ;;
    05-disasm/*)                   echo "disassembly da funcao" ;;
    06-decomp/*)                   echo "decompilacao da funcao" ;;
    07-strings/*)                  echo "strings filtradas" ;;
    08-kernel/*)                   echo "artefatos de kernelcache" ;;
    09-diff/*)                     echo "diff entre builds" ;;
    checksums.txt.sha1)            echo "checksum sha1 do IPSW" ;;
    *)                             echo "outro" ;;
  esac
}

echo "[" > "$TMP"
first=1

while IFS= read -r f; do
  rel="${f#./}"
  kind="$(tipo_de "$rel")"
  [ -n "$kind" ] || continue
  bytes=$(wc -c < "$rel" | tr -d ' ')
  if [ "$bytes" -gt "$LIMIT" ]; then
    echo "ERRO: $rel tem $bytes bytes (limite $LIMIT)" >&2
    exit 1
  fi
  sym="$(simbolo_de "$rel")"
  purpose="$(proposito_de "$rel")"
  sha=$(shasum -a 256 "$rel" | cut -d' ' -f1)
  [ "$first" -eq 1 ] || echo "," >> "$TMP"
  first=0
  printf '  {"path":"%s","kind":"%s","symbol":"%s","purpose":"%s","bytes":%s,"sha256":"%s"}' \
    "$rel" "$kind" "$sym" "$purpose" "$bytes" "$sha" >> "$TMP"
done < <(find . -type f \
  -not -path './_tmp/*' \
  -not -path './.git/*' -not -path './docs/*' \
  -not -name 'INDEX.json' -not -name '*.sh' \
  -not -name 'README.md' -not -name 'params.env' \
  -not -name '.gitignore' -not -name '.gitattributes' \
  | sort -t/ -k2,2 -k1,1)

echo "" >> "$TMP"
echo "]" >> "$TMP"
mv "$TMP" "$OUT"

python3 -c 'import json,sys; d=json.load(open("INDEX.json")); print("itens:", len(d))'
