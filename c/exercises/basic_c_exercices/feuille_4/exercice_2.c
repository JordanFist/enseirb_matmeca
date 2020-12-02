#include <stdio.h>
#include <stdlib.h>

void min_max(int l, int t[], int *min, int *max)
{
  printf("%d\n", *max);
  *min = t[0];
  *max = t[0];  
  for (int i = 1; i < l; ++i) {
    if (t[i] > *max) 
      *max = t[i];
    else
      *min = t[i];
  }
}

int main(int argc, char *argv[])
{
  //int tab[] = {1, 3, 5, 7, 8, 2};
  int l = atoi(argv[1]);
  int min = 0;
  int max = 0;
  int *tab;
  tab = (int) malloc(l * sizeof(int));
  for (int i = 2; i < l + 2; ++i) 
    tab[i - 2] = atoi(argv[i]);

  min_max(l, tab, &min, &max);
  printf("min : %d , max : %d \n",min, max);
  return 0;
}
    
