#include <stdio.h>

#include "Chaine.hpp"

void annexe(const Chaine &s) {
  printf("taille : %d\n", s.taille());
  printf("%c\n", s[1]);
}

/*
Chaine print(Chaine s) {
  Chaine chaine(s);
  chaine.debug();
  return s;
}*/

int main() {
  Chaine s1("une chaine");
  Chaine s2 (" complexe");
  s1 = s1 + s2;

  s1.debug();

  printf("%s\n", (const char *) (s1 + s2));
}
