#include <stdio.h>
#include <ctype.h>
#include <string.h>

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
  int signe = 0;
  int i = 0;
  if (val < 0) {
    val = -val;
    signe = 1;
  }
  while (val) {
    s[i] = (val % 10) + '0'; // permet de transformer un entier en un caractère
    val = val / 10;
    ++i;
  }
  if (signe) {
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
  
