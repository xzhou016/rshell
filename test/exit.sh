echo
./bin/rshell <<EOF
echo "[ src ] && (test src)"
echo test src && ls -a) &&  exit || test junk
exit
EOF