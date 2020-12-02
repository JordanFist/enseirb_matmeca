#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double a, double b, double c, double x)
{
  return a * pow(x,2) + b * x + c;
}

/*
int main(int argc, char *argv[])
{
  double x = 0;
  if (argc < 5) {
    printf("Veuillez donner x\n");
    scanf("%lf", &x);
  } else {
    x = atoi(argv[4]);
  }
  
  double a = atoi(argv[1]);
  double b = atoi(argv[2]);
  double c = atoi(argv[3]);
  
  double res = f(a ,b, c, x);
  printf("%f\n", res);
}
*/

double racine(double f)
{
  return sqrt(f);
}


int main(int argc, char *argv[])
{
  double a = atoi(argv[1]);
  double b = atoi(argv[2]);
  double c = atoi(argv[3]);
  double x = atoi(argv[4]);
  double res = f(a, b, c, x);
  if (res > 0) {
    double racine_res = racine(res);
    printf("%f : %f\n", res, racine_res);
  } else {
    double racine_res = racine(-res);
    printf("%f : i%f\n", res, racine_res);
  }
}
