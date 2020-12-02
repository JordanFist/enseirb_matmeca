#include <stdio.h>

#include "set.h"

void int__print(void * p) {
  int * _p = (int *)p;
  printf("%d ", *_p);
}


int main() {
  struct set * s = set__empty();

  int v1 = 8, v2 = 5, v3 = 15, v4 = 3;
  set__add(s, &v1);
  set__add(s, &v2);
  set__add(s, &v3);
  set__add(s, &v4);

  set__debug_data(s, int__print);
  printf("\n");
  
  v2 = 17;
  set__debug_data(s, int__print);
  printf("\n");

  set__free(s);

  return 0;
}
