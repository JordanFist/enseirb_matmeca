#ifndef CHAINE_HPP
#define CHAINE_HPP

#include "SmartPointer.hpp"

namespace enseirb
{

class Chaine
{
private:
  unsigned int _taille;
  SmartPointer<char> _donnees;

  void release();

public:
  Chaine();
  Chaine(const char *);

public:
  //Chaine(const Chaine &s);
  ~Chaine();
  //Chaine &operator=(const Chaine &);

public:
  unsigned int taille() const;
  char operator[](int indice) const;
  //operator char const *(void)const;
};
} // namespace enseirb

#endif
