#!/bin/bash
# prepare_test_files.sh

set -e

mkdir -p tests/test01 tests/test02 tests/test03 tests/test04

#---------------------------------------
# TEST01:
cat <<EOL > tests/test01/input.txt
entity
EOL

cat <<EOL > tests/test01/output.txt
Enter a word: entity

entity in Pig Latin is: entityyay
EOL

#---------------------------------------
# TEST02:

cat <<EOL > tests/test02/input.txt
pikmin
EOL

cat <<EOL > tests/test02/output.txt
Enter a word: pikmin

pikmin in Pig Latin is: ikminpay
EOL

#---------------------------------------
# TEST03:
cat <<EOL > tests/test03/input.txt
Kingdom
EOL

cat <<EOL > tests/test03/output.txt
Enter a word: Kingdom

kingdom in Pig Latin is: ingdomkay
EOL

#---------------------------------------
# TEST04:
cat <<EOL > tests/test04/input.txt
HEARTS
EOL

cat <<EOL > tests/test04/output.txt
Enter a word: HEARTS

hearts in Pig Latin is: eartshay
EOL
