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

void chaine_miroir(char *chaine_1, char *chaine_2)
{
  int n = len(chaine_1);
  for (int i = 0; i < n; ++i) 
    chaine_2[i] = chaine_1[n - i - 1];
}

int main(int argc, char *argv[])
{
  char *chaine_1 = argv[1];
  int n = len(chaine_1);
  char chaine_2[n];
  chaine_miroir(chaine_1, chaine_2);
  printf("%s\n", chaine_2);
  return 0;
}
  
// char *chaine_1 = char chaine_1[]
      
