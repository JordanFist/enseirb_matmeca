#include <stdio.h>
#include <stdlib.h>

void swap(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

/*
int main(int argc, char *argv[])
{
  int a = 5;
  int b = 6;
  swap(&a, &b);
  printf("%d %d\n", a, b);
}
*/

void order(int* a, int* b, int* c)
{
  if (*b < *a) {
    swap(a, b);
  }
  if (*b < *c) 
    printf("%d : %d : %d\n", *a, *b ,*c);
  else if (*a < *c) {
    swap(b, c);
    printf("%d : %d : %d\n", *a, *b ,*c);
  } else {
      swap(b, c);
      swap(a, b);
      printf("%d : %d : %d\n", *a, *b ,*c);
  }
}

int main(int argc, char *argv[])
{
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  int c = atoi(argv[3]);
  order(&a, &b, &c);
}
