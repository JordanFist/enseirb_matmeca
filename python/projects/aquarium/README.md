# Aquarium
The goal of this project is to have an aquarium thanks to a network of computers. One computer in the network is regarded as the server and other computers in the network connecting to the server are clients. Each client has a view within the aquarium which is not necessarily the view of the entire aquarium. The client asks which part of the aquarium he wants to see. Each client brings a new fish to the aquarium. The server allows synchronizing the display of fish for all clients.

The server is in C, clients are in python.

# Membres:
- Jordan Sandri
- Lucas Barros de Assis
- Reda Bonna
- Terence Lee-chao-shit
- Mehdy Salimi

Pour lancer le projet sur les ordinateurs de l'école, il faut créer l'environement virtuel en lancant le fichier setup.sh puis il faut l'activer en tapant à la racine du projet la commande suivante :

** source aquarium_project/bin/activate **

Pour exécuter le projet :
-------------------------

Aller dans server/src et lancer le Makefile commande make puis exécuter a.out. Creer une vue avec "add view N1 0x0+100+100" par exemple.
Puis aller dans client/src/ et lancer avec python3 Main.py puis ajouter un poisson avec "AddFish test at 50x50, 15x17, RandomWayPoint" par exemple, puis starter le poisson.
