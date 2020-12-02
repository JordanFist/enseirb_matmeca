#include <stdio.h>

#include "../set/set.h"
#include "link.h"
#include "set_link.h"

int main() {
  struct set * s = set__empty();

  int v1 = 1, v2 = 5, v3 = 8, v4 = 12;
  set__add(s, &v1);
  set__add(s, &v2);
  set__add(s, &v3);
  set__add(s, &v4);

  int v5 = 12;
  printf("Taille de s: %u (attendu: 4)\n", set__size(s));
  printf("%d appartient à s? %s (attendu: OUI)\n",
	 v5, (set__find(s, &v5) ? "OUI" : "NON"));

  set__free(s);

  return 0;
}
