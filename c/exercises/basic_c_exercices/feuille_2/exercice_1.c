#include <stdio.h>

/*
int main(int argc, char *argv[])
{
  int i = 0;
  while (i < argc) {
    printf("%s : %d \n ", argv[i], i);
    ++i;
  }
  return 0;
}
*/

int lengthcompare(char *chaine_1, char *chaine_2)
{
  int i = 0;
  while (chaine_1[i] != 0 && chaine_2[i]!= 0) 
    {
    ++i;
    }
  if (chaine_1[i] == 0 && chaine_2[i] == 0) {
    return 1;
  }
  return 0;
}

/*
int main(int argc, char *argv[])
{
  char *chaine_1 = argv[1];
  char *chaine_2 = argv[2];
  int res = lengthcompare(chaine_1, chaine_2);
  printf("%d\n", res);
  return 0;
}
*/

int voyelle(char *chaine)
{
  int i = 0;
  int res = 0;
  while (chaine[i] != 0)
    {
      if (chaine[i] == 'a' || chaine[i] == 'e' || chaine[i] == 'i' || chaine[i] == 'o' || chaine[i] == 'u' || chaine[i] == 'y') {
	++res;
      }
      ++i;
    }
  return res;
}


int main(int argc, char *argv[])
{
  
  char *chaine = argv[1];
  int res = voyelle(chaine);
  printf("%d\n", res);
  return 0;
}
