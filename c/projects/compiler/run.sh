#!/bin/bash

# ======================
# Programme d'éxécution
# ======================

if [ $# -ne 1 ]
then
    echo "ERREUR : Le nombre d'argument est invalide -> Fournir qu'un seul fichier"
else
    make clean all
    ./parse $1
    make test
    clear
    echo "Debut de l'affichage :"; echo
    ./test
fi
