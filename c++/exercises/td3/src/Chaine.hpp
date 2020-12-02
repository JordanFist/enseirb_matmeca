#ifndef CHAINE_HPP
#define CHAINE_HPP

class Chaine {
    unsigned int _taille;
    char *_donnees;

  public:
    char get(unsigned int i);
    Chaine();
    Chaine(const char *s);
    ~Chaine();
    unsigned int taille() const;
    Chaine (const Chaine &chaine);
    const Chaine& operator=(const Chaine &chaine);
    void debug() const ;
};

#endif
