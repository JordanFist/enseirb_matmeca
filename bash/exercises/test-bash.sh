# file: #.sh
#date: jeu. oct. 12 10:45:29 CEST 2017
#author:vta <jsandri@enseirb-matmeca.fr>
#description:
#

#!/bin/bash
CMD=skeleton2.sh

usage()
{
    echo "usage: $CMD"
}

if [ $# -ne 1 ]
then
    usage
    exit 1
fi
