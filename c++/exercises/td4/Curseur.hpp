#ifndef CURSEUR_HPP
#define CURSEUR_HPP

#include "Chaine.hpp"

class Curseur {
protected:
    Chaine _chaine;
    int _position;
public:
    Curseur(const Chaine& chaine);
    virtual ~Curseur();
    
public:
    //entier& operator++(); //prefixe
    //entier operator++(int); //postfixe
    char operator*();
    virtual Curseur& operator++() =0;
    virtual Curseur& operator--() =0;
    virtual bool fini() const =0;
    virtual void debut() =0;
    virtual void fin() =0;
};

#endif