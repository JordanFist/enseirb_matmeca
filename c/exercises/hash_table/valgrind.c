#include <stdio.h>
#include <stdlib.h>
/*
void afficher() {
  int tab[10];
  for (int i = 0; i <= 10; ++i) 
    tab[i] = 0;
  for (int i = 0; i <= 10; ++i)
    printf("%d : %d\n", i + 1, tab[i]);
}
*/

void alloc() {
  int *tab = malloc(10 * sizeof(int));
  for (int i = 0; i < 10; ++i) 
    tab[i] = 0;
  for (int i = 0; i <= 10; ++i)
    printf("%d : %d\n", i + 1, tab[i]);
  free(tab);
}

int main(int argc, char *argv[]) {
  //afficher();
  alloc();
  return 0;
}
