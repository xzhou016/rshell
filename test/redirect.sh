#!/bin/sh
### Input Redirection test ###
./bin/rshell <<EOF
cat < testIO/testInput
A-Z < testIO/testInput

***add more here

ls > testIO/testOutput
echo muh test > testIO/testOutput

exit
EOF
