CXX=g++
CXXFLAGS=-Wall -g 

Programme: Programme.o Chaine.o Curseur.o CurseurClassique.o CurseurInverse.o CurseurPas.o
	$(CXX) $(CXXFLAGS) $^ -o $@

Programme.o: Programme.cpp Chaine.cpp Curseur.cpp CurseurClassique.cpp CurseurInverse.cpp CurseurPas.cpp

Chaine.o: Chaine.cpp Chaine.hpp 

Curseur.o: Curseur.cpp Curseur.hpp

CurseurClassique.o: CurseurClassique.cpp CurseurClassique.hpp

CurseurInverse.o: CurseurInverse.cpp CurseurInverse.hpp

CurseurPas.o: CurseurPas.cpp CurseurPas.hpp

clean:
	rm Programme *.o