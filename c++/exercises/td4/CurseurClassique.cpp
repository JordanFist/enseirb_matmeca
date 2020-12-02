#include "Curseur.hpp"
#include "CurseurClassique.hpp"
#include <cstdio>
#include <cstring>

CurseurClassique::CurseurClassique(const Chaine& chaine) :
    Curseur(chaine) 
    {}

CurseurClassique::~CurseurClassique() {
}

void afficheCurseur(Curseur& curseur) {
    curseur.debut();
    while(!curseur.fini()){
        printf("%c", *curseur);
        ++curseur;
    }
    printf("%c", *curseur);
    printf("\n");
}

Curseur& CurseurClassique::operator++() {
    _position++;
    return *this;
}

Curseur& CurseurClassique::operator--() {
    _position--;
    return *this;
}

bool CurseurClassique::fini() const{
    return ((unsigned int)_position == _chaine.taille());
}

void CurseurClassique::debut() {
    _position = 0; 
}

void CurseurClassique::fin() {
    _position = _chaine.taille(); 
}