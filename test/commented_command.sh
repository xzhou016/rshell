echo
./bin/rshell <<EOF
echo "(((test -d src))#)"
(((test -d src))#)
echo "(([ -f src ])# && (test -f src))"
(([ -f src ])# && (test -f src))
echo "((test src && ls -a) && test junk)#"
((test src && ls -a) && test junk)#
exit
EOF