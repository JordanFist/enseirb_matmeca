#include "Chaine.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

Chaine::Chaine() {
    printf("%s(%d):%s\n",__FILE__,__LINE__,__func__);
}

Chaine::Chaine(const char *s) {
    _donnees = new char[_taille + 1];
    strcpy(_donnees, s);
    printf("%s(%d):%s\n",__FILE__,__LINE__,__func__);
}

Chaine::Chaine(const Chaine &chaine)
    :_taille(chaine._taille),
    _donnees(new char[_taille + 1])
    {
        strcpy(_donnees, chaine._donnees);
    }

unsigned int Chaine::taille() const {
    return _taille;
}

void Chaine::debug() const{
    printf("%s\n", _donnees);
}

char Chaine::get(unsigned int i) {
    unsigned int j = 0;
    while (_donnees[j] != 0) {
        if (j == i)
            return _donnees[j];
        ++j;
    }
    printf("i est plus grand que la taille du mot");
    return -1;
}

const Chaine& Chaine::operator=(const Chaine &chaine) {
    if (this == &chaine)
        return *this;
    delete[] _donnees;
    _taille = chaine._taille;
    _donnees = new char[_taille + 1];
    return chaine;
}

Chaine::~Chaine() {
    delete[] _donnees;
    printf("%s(%d):%s\n",__FILE__,__LINE__,__func__);
}
