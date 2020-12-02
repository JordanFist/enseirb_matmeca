#include<cstdio>

#include "Chaine.hpp"
#include "Curseur.hpp"
#include "CurseurClassique.hpp"
#include "CurseurInverse.hpp"
#include "CurseurPas.hpp"


void affiche(const Chaine &s){
  std::puts("affiche:");
  for(unsigned int i = 0; i < s.taille(); i++)
    std::putchar(s[i]);
  std::puts("");
}

int main(int argc, char **argv){
  /*
  Chaine s("un texte long");
  Chaine p("test");
  Chaine copie=p;


  affiche(s);
  affiche(p);
  affiche(copie);

  p=s;
  
  affiche(s);
  affiche(p);
  affiche(copie);
  */

  Chaine chaine("test");
  CurseurClassique curseurClassique(chaine);
  afficheCurseur(curseurClassique);

  CurseurInverse curseurInverse(chaine);
  afficheCurseur(curseurInverse);

  CurseurPas curseurPas(chaine, 1, 4, 1);
  afficheCurseur(curseurPas);
  //curseurClassique.fin();
  //printf("%d", curseurClassique.fini());
}
