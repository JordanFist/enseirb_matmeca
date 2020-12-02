#include <stdio.h>

int len(char *chaine)
{
  int i = 0;
  while (chaine[i] != 0)
    {
      ++i;
    }
  return i;
}

// char *chaine_1 = char chaine_1[]

char chaine_mirroir(char *chaine_1)
{
  int n = len(chaine_1);
  char chaine_2[n + 1];
  chaine_2[n + 1] = 0;
  for (int i = 1; i < n + 1; ++i)
      chaine_2[i] = chaine_1[n - i];
  return chaine_2;
}


int main(int argc, char *argv[])
{
  char *chaine_1 = argv[1];
  chaine_mirroir(chaine_1);
  char *chaine_2 = chaine_mirroir(chaine_1);
  printf("%c\n", chaine_2);
  return 0;
}
      
