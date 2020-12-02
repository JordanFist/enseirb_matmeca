#include "CurseurPas.hpp"
#include "Curseur.hpp"

CurseurPas::CurseurPas(const Chaine& chaine, const int position, const int posFin, const int pas) : 
Curseur(chaine),
_positionFin(posFin),
_pas(pas)
{
    _position = position;

}

CurseurPas::~CurseurPas() {}

Curseur& CurseurPas::operator++() {
    _position = _position + _pas;
    return *this;
}

Curseur& CurseurPas::operator--() {
    _position = _position - _pas;
    return *this;
}

bool CurseurPas::fini() const{
    return ((unsigned int)_position == _chaine.taille());
}

void CurseurPas::debut() {
    _position = 0; 
}

void CurseurPas::fin() {
    _position = _positionFin; 
}