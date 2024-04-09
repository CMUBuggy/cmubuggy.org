#!/bin/sh
#
# Simple script to clean up character set of history imports.
# Usage: ./sed_history_dump.sh [import file]
sed -i 's/utf8mb4_0900_ai_ci/utf8mb4_unicode_520_ci/g' $1
