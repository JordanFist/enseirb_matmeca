#include <stdio.h>
#include <string.h>
/*
int strlen(char *str)
{
  int len = 0;
  while (str[len])
    ++len;
  return len;
}
*/

int strcnp (char *s1, char *s2)
{
  int i = 0;
  while (s2[i]) {
      if (!s1[i])
	return -1;
      ++i;
    }
  return s1[i] != 0;
}

void mirroir (char *s)
{
  int l = strlen(s);
  int i = 0;
  int m = l/2;
  char tmp;
  while (i < m) {
      tmp = s[i];
      s[i] = s[l - (i + 1)];
      s[l - (i + 1)] = tmp;
      ++i;
    }
}

void itoa(int val, char *s)
{
  int moy = 0;
  int i = 0;
  if (val < 0) {
    val = -val;
    moy = 1;
  }
  while (val) {
    s[i] = (val % 10) + '0'; // permet de transformer un entier en un caractère
    printf("%c : %d\n", s[i], val);
    val = val / 10;
    ++i;
  }
  if (moy) {
    s[i] = '-';
    ++i;
  }
  s[i] = 0;
  mirroir(s);
}

int main(int argc, char *argv[])
{
  
  int val = -995;
  char s[4];
  itoa(val, s);
  printf("%s\n", s);
}


