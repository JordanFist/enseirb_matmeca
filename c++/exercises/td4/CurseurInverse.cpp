#include "Curseur.hpp"
#include "CurseurInverse.hpp"

CurseurInverse::CurseurInverse(const Chaine& chaine) :
Curseur(chaine)
{
    _position = _chaine.taille();
}

CurseurInverse::~CurseurInverse() {
}


Curseur& CurseurInverse::operator++() {
    _position--;
    return *this;
}

Curseur& CurseurInverse::operator--() {
    _position++;
    return *this;
}

bool CurseurInverse::fini() const{
    return ((unsigned int)_position == 0);
}

void CurseurInverse::debut() {
    _position = _chaine.taille(); 
}

void CurseurInverse::fin() {
    _position = 0; 
}