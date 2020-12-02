# Compiler

Creation of a compiler in C, Lex and yacc.

README
======

Modications : Test qui ne passait pas le vendredi 7 décembre
ex : x = 4;
     let x = 5.1 in (x+1.4);

Ceci fonctionne maintenant, puisqu'on on crée deux variables x de type respectivement int et float.
Concrétement, lorsque l'on entre dans un let on ajoute en tête de la liste des symboles un nouvel élèment possèdant
le sid de x mais auquel est associé une nouvelle valeur de type float et contenant le registre où est stocké 5.1 
Quand on sort du let on enlève cette valeur de la liste.
Pour les déclarations de variable dans test.h, on suffixe chaque nom de variable par un entier égal au nombre
de déclarations de variable déjà faites. 
Ceci n'est pas forcèment optimal parce que chaque affectation conduit à créer une nouvelle variable mais en contrepartie cela nous permet de déclarer successivement une variable de type entier puis flotant ou flotant puis entier.

Composition du répertoire :
===========================

Ce répertoire est composé de 3 dossiers :
- src : Contient les fichiers src et les headers (C + yacc)
- tst : Contient les fichiers avec des codes sources .myml
- build : Contient les .o, le header et le code généré par yacc

Ce répertoire contient également un Makefile avec les commandes make et clean.

Cependant, il est préférable de lancer le script run.sh comme ceci :
** ex: ./run.sh fichier_source.myml **
