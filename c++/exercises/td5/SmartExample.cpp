#include "SmartPointer.hpp"
#include "Chaine.hpp"

#include <cstdio>

void f(int *p)
{
  printf("%d\n", *p);
}

void f(float *p)
{
  printf("%f\n", *p);
}

int main()
{
  using enseirb::SmartPointer;
  SmartPointer<int> p(new int(10));
  SmartPointer<int> q(p);

  //SmartPointer<int> buggy(new int[10]); // on a aloué un tableau et on le désalloue avec delete et pas delete[]

  //SmartPointer<Chaine> r(new Chaine());

  f(p);

  *p = 5;
  f(q);
}
