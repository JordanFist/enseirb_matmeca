ls -lt | tr -s " " | cut -d\  -f 9 | head -$1
echo""
echo "Voulez-vous creer une arhive à partir de l'un de ces fichiers ? (y/n)"

read 

if [ $REPLY = "yes" ] || [ $REPLY = "y" ]
then
    echo "Quel fichier voulez-vous archiver ?"
    read
    tar -cvzf archive-$REPLY $REPLY
elif [ $REPLY = "no" ] || [ $REPLY = "n" ]
then
    exit 1
else
    echo "ERREUR"
    exit 1
fi

# on peut aussi faire 
# read answer
# $answer = "y"
