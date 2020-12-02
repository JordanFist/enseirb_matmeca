#include <stdio.h>

int fibo_rec(int n) {
  if (n == 0) {
    return 0;
      }
  if (n == 1) {
    return 1;
  }
  return fibo_rec(n-1) + fibo_rec(n-2);
}

int main(int argc, char *argv[]) {
  int n = 3;
  printf("%d\n", fibo_rec(n));
}
