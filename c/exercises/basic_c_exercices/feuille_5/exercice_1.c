#include <stdio.h>
#include <math.h>

void min_max(int len, double tab[], double* min, double* max)
{
  for (int i = 0; i < len; ++i) {
    if (tab[i] < *min) 
      *min = tab[i];
    if (*max < tab[i])
      *max = tab[i];
  }
}

int main(int argc, char *argv[])
{
  double max = 0;
  double min = 0;
  double tab[] = {1, 3, 6.2, 18.1, -2.};
  int len = 5;
  min_max(len, tab, &min, &max);
  printf("min : %f\nmax : %f\n", min, max);
  return 0;
}
