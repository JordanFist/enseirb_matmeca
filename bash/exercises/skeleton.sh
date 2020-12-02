function entete () {
echo "$1 file: $1.sh
$1date: `date`
$1author:vta <$USER@enseirb-matmeca.fr>
$1description:
$1"
}

function bash_skeleton () {
echo "
#!/bin/bash
CMD=`basename $0`

usage()
{
    echo \"usage: \$CMD\"
}

if [ \$# -ne 1 ]
then
    usage
    exit 1
fi" 
}

function latex_skeleton () {
echo "%
\documentclass{article}
%\usepackage{}
\begin{document}
\end{document}" 
}

if [ $# -ne 2 ] || ([ $2 != "latex" ] && [ $2 != "bash" ])
then 
    echo "usage"
    exit 1
elif [ $2 = "bash" ]
then
    entete "#" > test-bash.sh
    bash_skeleton $1 >> test-bash.sh
elif [ $2 = "latex" ] 
then
    entete "%" > test-latex.tex
    latex_skeleton $1 >> test-latex.tex
fi


