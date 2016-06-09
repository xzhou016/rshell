#!/bin/sh
### Input Redirection test ###
../bin/rshell <<EOF
cat < testIO/testInput
A-Z < testIO/testInput

ls > testIO/testOutput
echo muh test > testIO/testOutput
A-Z > testIO/testOutput
echo test > testIO/testOutput

ls | echo
cat | grep
ps | ls
cat < testIO/testInput | tr A-Z a-z | tee testOput | tr a-z

exit
exit
EOF
