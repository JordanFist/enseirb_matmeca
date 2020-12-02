#include <stdio.h>

void pascal_ligne(int len, int valeurs[])
{
  int i = 1;
  int x = 1;
  int y = valeurs[i];
  while (i < len) {
    valeurs[i] = valeurs[i] + x;
    x = y;
    y = valeurs[i + 1];
    i = i + 1;
  }
  valeurs[len] = 1; 
}

void afficher(int len, int tab[])
{
  int i = 0;
  while (i < len) {
    printf("%d ", tab[i]);
    i = i + 1;
  }
}

/*
int main(int argc, char *argv[])
{
  int tab[] = {1,3,3,1};
  int len = 4;
  pascal_ligne(len ,tab);
  afficher(len + 1, tab);
}
*/

void affiche_pascal(int n)
{
  int i = 0;
  int len = 1;
  int tab[] = {1, 1};
  while (i < n) {
    afficher(len, tab);
    pascal_ligne(len, tab);
    printf("\n");
    len = len + 1;
    i = i + 1;
  }
}

/*
int main(int argc, char *argv[])
{
  int n = 7;
  affiche_pascal(n);
}
*/


    
