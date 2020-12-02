# Ne jamais compiler les headers

SmartExample: SmartExample.o Chaine.o #SmartPointer.o
	g++ -Wall -o SmartExample SmartExample.o Chaine.o #SmartPointer.o

SmartExample.o: SmartExample.cpp SmartPointer.hpp 
	g++ -c SmartExample.cpp

SmartPointer.o: SmartPointer.cpp SmartPointer.hpp 
	g++ -c SmartPointer.cpp

Chaine.o: Chaine.cpp Chaine.hpp 
	g++ -c Chaine.cpp

clean: 
	rm -f *.o SmartExample
