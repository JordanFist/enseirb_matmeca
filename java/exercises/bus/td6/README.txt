On retrouve dans ce répertoire 5 sous répertoires:
- build : Contient toutes les .class (src + tst)
- src : Contient les fichiers src
- tst : Contient les fichiers tests

- abstract : Contient les répertoires du td4 avec la 
modification n°1 -> classes concrètes publiques
- interface : Contient les répertoires du td4 avec la 
modification n°2 -> classes concrètes internes au package

On trouve également un Makefile, avec les commandes build, 
run et clean dans le répertoire mère mais aussi dans les 
répertoires abstract et interface. La commande make réalise 
build et run. Elle lance les tests de TestJauge et 
TestPosition mais aussi ceux de TestAutobus et 
TestPassagerStandard. Elle exécute également le client (Simple.java)
