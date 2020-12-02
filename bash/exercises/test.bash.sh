echo "# file: $1.sh
#date: `date`
#author:vta <$USER@enseirb-matmeca.fr>
#description:
#

#!/bin/bash
CMD='basename $0'

usage()
{
    echo "usage: $CMD"
}

if [ $# -lt 10 ]
then
    usage
    exit 1
fi
" > test-bash.sh
