#! /usr/bin/env bash
ROWS={$1:-55}
COLS={$2:-80}
printf '\e[8;%d;%dt' "$ROWS" "$COLS"
