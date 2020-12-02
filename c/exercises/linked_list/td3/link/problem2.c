#include <stdio.h>

#include "set.h"

int main() {
  struct set * s1 = set__empty();
  int v1 = 7, v2 = 3, v3 = 13, v4 = 1;
  set__add(s1, &v1);
  set__add(s1, &v2);
  set__add(s1, &v3);
  set__add(s1, &v4);

  struct set * s2 = set__empty();
  int w1 = 7, w2 = 3, w3 = 13, w4 = 1;
  set__add(s2, &w1);
  set__add(s2, &w2);
  set__add(s2, &w3);
  set__add(s2, &w4);

  printf("Taille de s1: %u (attendu: 4)\n", set__size(s1));
  printf("Taille de s2: %u (attendu: 4)\n", set__size(s2));
  printf("v1=%d appartient à s1? %s (attendu: OUI)\n",
	 v1, (set__find(s1, &v1) ? "OUI" : "NON"));
  printf("v1=%d appartient à s2? %s (attendu: OUI)\n",
	 v1, (set__find(s2, &v1) ? "OUI" : "NON"));

  set__free(s1);
  set__free(s2);

  return 0;
}
