#include <stdio.h>
#include <ctype.h>

int len(char *chaine)
{
  int i = 0;
  while (chaine[i] != 0)
    {
      ++i;
    }
  return i;
}

int palindrome(char *chaine)
{
  int i = 0;
  int n = len(chaine);
  int res = 1;
  while (i < n/2)
    {
      if (chaine[i] != chaine[n - i - 1]) {
	res = 0;
      }
      ++i;
    }
  return res;
}

/*
int main(int argc, char *argv[])
{
  char *chaine = argv[1];
  int res = palindrome(chaine);
  printf("%d\n", res);
  return 0;
}
*/

/*
int main(int argc, char *argv[])
{
  int res = isalpha('a');
  printf("%d\n", res);
  return 0;
}
*/

/*
int main(int argc, char *argv[])
{
  char res = tolower('A');
  printf("%c\n", res);
  return 0;
}
*/

//Engage le jeu que je le gagne

int palindrome_2(char *chaine)
{
  int i = 0;
  int n = len(chaine);
  int j = n - 1;
  int res = 1;;
  while (i < n/2)
    {
      if (chaine[i] == ' ') {
	++i;
      }
      if (chaine[j] == ' ') {
	--j;
      }
      if (chaine[i] != chaine[j]) {
	res = 0;
	printf("%c : %c : %d : %d\n", chaine[i], chaine[j], i, j);
      }
      ++i; --j;
    }
  return res;
}


int main(int argc, char *argv[])
{
  char *chaine = argv[1];
  int res = palindrome_2(chaine);
  printf("%d\n", res);
}

