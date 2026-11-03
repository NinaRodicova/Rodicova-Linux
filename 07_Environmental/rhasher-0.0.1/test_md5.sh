#!/bin/sh

EXPECTED=$(printf 'pink' | md5sum | awk '{print toupper($1)}')
ACTUAL=$(./rhasher MD5 '"pink"' | tr -d '\n')
if [ "$EXPECTED" != "$ACTUAL" ]; then
    echo "FAIL: MD5 string"
    echo "  expected: $EXPECTED"
    echo "  actual:   $ACTUAL"
    exit 1
fi

TMPFILE=$(mktemp)
trap 'rm -f "$TMPFILE"' EXIT
printf 'pink\n' > "$TMPFILE"

EXPECTED=$(md5sum "$TMPFILE" | awk '{print toupper($1)}')
ACTUAL=$(./rhasher MD5 "$TMPFILE" | tr -d '\n')
if [ "$EXPECTED" != "$ACTUAL" ]; then
    echo "FAIL: MD5 file"
    echo "  expected: $EXPECTED"
    echo "  actual:   $ACTUAL"
    exit 1
fi

echo "PASS: SHA1"
exit 0
