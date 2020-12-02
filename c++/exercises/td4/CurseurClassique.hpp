#ifndef CURSEURCLASSIQUE_H
#define CURSEURCLASSIQUE_H

#include "Curseur.hpp"

class CurseurClassique : public Curseur {
public:
    CurseurClassique(const Chaine& chaine);
    virtual ~CurseurClassique();

public:
    Curseur& operator++();
    Curseur& operator--();
    bool fini() const;
    void debut();
    void fin();
};

void afficheCurseur(Curseur& curseur);

#endif