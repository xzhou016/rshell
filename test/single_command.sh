echo
./bin/rshell <<EOF
ls -a
echo hello
git status
echo "What "
mkdir test
exit
EOF