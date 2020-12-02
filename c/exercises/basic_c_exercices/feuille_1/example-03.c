#include <stdio.h>

int somme(int tab[], int n) {
  int i = 0;
  int res = 0;
  while (i < n) {
    res = res + tab[i];
    i = i+1;
  }
  return res;
}

//int main(int argc, char *argv[]) {
//  int tab[] 0 ={0,2,4,7};
//  int n = 4;
//  int res = somme(tab,n);
//  printf("%d\n", res);
//  return 0;
//    }

int produit(int tab_1[],int tab_2[],int n) {
  int i = 0;
  int res = 0;
  while (i < n) {
    res = res+tab_1[i]*tab_2[i];
    i = i+1;
  }
  return res;
}

//int main(int argc, char *argv[]) {
//  int tab_1[] = {0,1,2};
//  int tab_2[] = {0,1,3};
//  int n = 3;
//  int res = produit(tab_1,tab_2,n);
//  printf("%d\n", res);
//  return 0;
//}

int afficher(int tab[], int n) {
  int i = 0;
    while (i < n) {
      printf("%d\n", tab[i]);
      i = i+1;
    }
    return 0;
}
  
int somme_de_tableau(int tab_1[],int tab_2[],int n) {
  int i = 0;
  int tab_somme[] = {0,0,0} ;
  while (i < n) {
    tab_somme[i] = tab_1[i] + tab_2[i];
    i = i+1;
  }
  afficher(tab_somme,3);
  return 0;
}

int main(int argc, char *argv[]) {
  int tab_1[] = {0,1,2};
  int tab_2[] = {0,1,2};
  int n = 3;
  somme_de_tableau(tab_1,tab_2,n);
}


