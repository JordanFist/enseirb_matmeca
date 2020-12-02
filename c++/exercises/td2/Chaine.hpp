#ifndef CHAINE_HPP
#define CHAINE_HPP

#include <cstring>

class Chaine {
 private:
  char* _donnees;
  unsigned int _taille;

 public:
  Chaine();
  Chaine(const char*);
  ~Chaine();
  Chaine(const Chaine &chaine);
  const Chaine& operator=(const Chaine &chaine);
  const char& operator[](unsigned int i) const;
  operator const char *() const;
  const Chaine& operator+(const Chaine &chaine1) const;

  unsigned int taille() const;
  char get(unsigned int i);
  void debug() const;

};

#endif
