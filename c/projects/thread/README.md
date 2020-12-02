# OS project
Own implementation of the pthread library in C.

# Projet de systèmes d'explotation

Membres : 
- Sandri Jordan
- Heuillet Alexandre
- Rémi Garcia
- Jofrey Gaurivaud

Dans ce répertoire on trouve :
- src : contient les sources du projet
- tests: contient les tests des sources 
- Makefile avec les commandes citées dans le sujet
    
** Pour les utilisateurs de MacOS, nous compilons avec -Wno-deprecated-declarations pour éviter les warnings dû à un code qui n'est plus d'actualité et nous rajoutons la ligne #define _XOPEN_SOURCE 600 dans thread.h pour l'utilisation des fontions dans ucontext **
