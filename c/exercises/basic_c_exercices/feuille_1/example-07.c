#include <stdio.h>

void afficher(int len, int tab[])
{
  for (int i = 0; i < len; ++i)
    {
      printf("%d : %d\n", tab[i], i);
    }
}

void initialiser(int n,int tab[])
{
  for (int i = 0; i < n; ++i)
    {
      tab[i] = 1;
    }
}

void eratosthene(int n, int tab[])
{
  initialiser(n, tab);
  tab[0] = 0; tab[1] = 0;
  for (int i = 2; i < n; ++i)
    {
      if (tab[i] == 1) {
	for (int j = i + 1; j < n; ++j)
	  {
	    if (j % i == 0 && tab[j] == 1){
	      tab[j] = 0;
	    }
	  }
      }
    }
}

int main(int argc, char *argv[])
{
  int n = 100;
  int tab[n];
  eratosthene(n, tab);
  afficher(n, tab);
}
