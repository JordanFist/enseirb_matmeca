x=$1
shift

for i in $*
do
    echo -n "$x + $i = "
    x=$((x + $i))
    echo $x
done
