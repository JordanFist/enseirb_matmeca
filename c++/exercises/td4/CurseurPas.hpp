#ifndef CURSEURPAS
#define CURSEURPAS

#include "Curseur.hpp"

class CurseurPas : public Curseur {
public:
    int _positionFin;
    int _pas;
public:
    CurseurPas(const Chaine& chaine, const int position, const int posFin, const int pas);
    virtual ~CurseurPas();

public:
    Curseur& operator++();
    Curseur& operator--();
    bool fini() const;
    void debut();
    void fin();
};

#endif