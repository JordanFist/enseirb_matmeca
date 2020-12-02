#include <stdio.h>
#include <stdlib.h> // neccesaire pour utliser atoi

// atoi({'1','9',0}) = 19 ou atoi("1900") = 1900

int bissextiles(int annee)
{
  if (annee % 4 == 0 && annee % 100 != 0)
    return 1;
  else if (annee % 400 == 0)
    return 1;
  else 
    return 0;
}

/*
int main(int argc, char *argv[])
{
  int annee = atoi(argv[1]);
  int res = bissextiles(annee);
  printf("%d\n", res);
}
*/

int jour(int mois, int annee)
{
  if (bissextiles(annee) == 0 ) {
    if (mois == 2)
      return 29;
    else if (mois % 2 != 0 || mois == 8) 
      return 31;
    else 
      return 30;
  } else if (mois == 2)
    return 28;
  else if (mois % 2 != 0 || mois == 8) 
    return 31;
  else
    return 30;
}

int main(int argc, char *argv[])
{
  int mois = atoi(argv[1]);
  int annee = atoi(argv[2]);
  printf("%d\n", jour(mois, annee));
}

  

      


