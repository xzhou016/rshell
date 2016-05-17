echo
./bin/rshell <<EOF
ls -a; echo hello
ls; git status
echo "What "; echo meg; ls
exit
EOF