#include "Chaine.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

Chaine::Chaine() {
    printf("%s(%d):%s\n",__FILE__,__LINE__,__func__);
}

Chaine::Chaine(const char *s) {
    _donnees = NULL;
    _donnees = (char *)malloc(20 * sizeof(char));
    if (_donnees == NULL)
        exit(1);
    strcpy(_donnees, s);
    printf("%s(%d):%s\n",__FILE__,__LINE__,__func__);
}

unsigned int Chaine::taille() {
    return _taille;
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

//void Chaine::annexe(Chaine s) {}

Chaine::~Chaine() {
    free(_donnees);
    printf("%s(%d):%s\n",__FILE__,__LINE__,__func__);
}
