#include <stdio.h>
#include <ctype.h>

int taille(char *chaine)
{
  int i = 0;
  int res = 0;
  while (chaine[i]) {
    if (chaine[i] == ' ') 
      ++res;
    ++i;
  }
  return res + 1;
}

void afficher(int n, int tab[])
{
  int i = 0;
  while (i < n) {
    printf("%d\n", tab[i]);
    i++;
  }
}

void atoi(char *chaine, int tab[])
{
  int i = 0;
  int j = 0;
  int k = 0;
  char *s;
  while (chaine[i] != 0) {
    if (chaine[i] == ' ') {
      ++i;
      ++j;
      s[j] = 0;
      j = 0;
      tab[k] = atoi(s);
      ++k;
    }
    s[j] = chaine[i];
    ++i;
    ++j;
  }
}

int main(int argc, char *argv[])
{
  int n = taille(argv[1]);
  int tab[n];
  atoi(argv[1], tab);
  afficher(n, tab);
  return 0;
}
