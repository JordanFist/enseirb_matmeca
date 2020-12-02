#ifndef CHAINE_HPP
#define CHAINE_HPP

class Chaine {
    unsigned int _taille;
    char *_donnees;

  public:
    //void annexe(Chaine s);
    char get(unsigned int i);
    Chaine();
    Chaine(const char *s);
    ~Chaine();
    unsigned int taille();
};

#endif
