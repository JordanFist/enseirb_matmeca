#ps | grep $1

if [ $# -gt 0 ] ; then
    ps | grep $1
fi
