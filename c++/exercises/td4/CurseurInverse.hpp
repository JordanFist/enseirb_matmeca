#ifndef CURSEURINVERSE_HPP
#define CURSEURINVERSE_HPP

#include "Curseur.hpp"

class CurseurInverse : public Curseur {
public:
    CurseurInverse(const Chaine& chaine);
    virtual ~CurseurInverse();

public:
    Curseur& operator++();
    Curseur& operator--();
    bool fini() const;
    void debut();
    void fin();
};

#endif