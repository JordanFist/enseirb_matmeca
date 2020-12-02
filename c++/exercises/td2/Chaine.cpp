#include<cstdio>
#include <cstring>

#include "Chaine.hpp"

Chaine::Chaine(): _taille(0) {
  _donnees=NULL;
}

Chaine::Chaine(const char *s) {
  // Cas s==NULL a gerer plus tard.
  _taille = strlen(s);

  _donnees = new char[_taille + 1];
  strcpy(_donnees, s);
  
  std::printf("%s(%d): %s\n", __FILE__, __LINE__, __func__);
}

Chaine::~Chaine() {
  if (_donnees != NULL)
    delete[] _donnees;
  _donnees=NULL;
  std::printf("%s(%d): %s\n", __FILE__, __LINE__, __func__);
}

Chaine::Chaine(const Chaine &chaine) : _taille(chaine._taille) {
	_donnees = new char[strlen(chaine._donnees)];
	strcpy(_donnees, chaine._donnees);
	printf("copie\n");
}

const Chaine& Chaine::operator=(const Chaine& chaine) {
	printf("operator=\n");
	_taille = chaine._taille;
	if (_donnees != NULL)
		delete[] _donnees;
	
	_donnees = new char[strlen(chaine._donnees)];
  	strcpy(_donnees, chaine._donnees);
	return *this;
}

const char& Chaine::operator[](unsigned int i) const {
	return _donnees[i];
}

Chaine::operator const char *() const {
	return _donnees;
}

const Chaine& Chaine::operator+(const Chaine& chaine) const {
	Chaine *s = new Chaine(_donnees);
	strcat(s->_donnees, chaine._donnees);
	return *s;
}

unsigned int Chaine::taille() const {
    return _taille;
}

char Chaine::get(unsigned int i){
  if (_donnees==NULL) return '\0';
  if (i>_taille) return '\0';
  return _donnees[i];
}

void Chaine::debug() const {
  printf("_donnees : %s\n", _donnees);
}




