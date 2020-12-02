#include "Curseur.hpp"
#include "Chaine.hpp"
#include <cstdio>

Curseur::Curseur(const Chaine& chaine) :
    _chaine(chaine),
    _position(0)
{}

Curseur::~Curseur() {
}

char Curseur::operator*() {
    return _chaine[_position];
}