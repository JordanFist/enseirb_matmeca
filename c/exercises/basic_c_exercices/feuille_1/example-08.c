#include <stdio.h>

void afficher(int len, int tab[])
{
  int i = 0;
  while (i < len) {
    printf("%d ", tab[i]);
    i = i + 1;
  }
  printf("\n");
}

void tri_a_bulle(int len, int tab[])
{
  int i = 0;
  int j = 0;
  int x;
  int c;
  while (i < len - 1) {
    while (j < len - i - 1) {
      if (tab[j + 1] < tab[j]) {
	x = tab[j];
	tab[j] = tab [j + 1];
	tab[j + 1] = x;
	c = 1;
      }
      j = j + 1;
    }
    if (c == 0) {
      break;
    }
    j = 0;
    i = i + 1;
    c = 0;
  }
}

int main(int argc, char *argv[])
{
  int len = 10;
  int tab[] = {3,27,97,1,22,61,87,25,98,26};
  tri_a_bulle(len, tab);
  afficher (len, tab);
}
