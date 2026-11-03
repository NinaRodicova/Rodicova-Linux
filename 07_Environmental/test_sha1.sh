#!/bin/sh

EXPECTED=$(printf 'pink' | sha1sum | awk '{print toupper($1)}')
ACTUAL=$(./rhasher SHA1 '"pink"' | tr -d '\n')
if [ "$EXPECTED" != "$ACTUAL" ]; then
    echo "FAIL: SHA1 string"
    echo "  expected: $EXPECTED"
    echo "  actual:   $ACTUAL"
    exit 1
fi

TMPFILE=$(mktemp)
trap 'rm -f "$TMPFILE"' EXIT
printf 'pink\n' > "$TMPFILE"

EXPECTED=$(sha1sum "$TMPFILE" | awk '{print toupper($1)}')
ACTUAL=$(./rhasher SHA1 "$TMPFILE" | tr -d '\n')
if [ "$EXPECTED" != "$ACTUAL" ]; then
    echo "FAIL: SHA1 file"
    echo "  expected: $EXPECTED"
    echo "  actual:   $ACTUAL"
    exit 1
fi

echo "PASS: SHA1"
exit 0
