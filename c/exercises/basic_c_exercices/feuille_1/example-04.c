#include <stdio.h>

int trie(int tab[], int n) {
  int i = 0;
  int res = 1;
  while(i < n-1) {
    if (tab[i] > tab[i+1]) {
      res = 0;
	}
    i = i+1;
  }
  return res;
}

//int main(int argc, char *argv[]) {
//  int tab[]={0,1,2,5};
//  int n = 4;
//  int res = trie(tab,n);
//  printf("%d\n", res);
//}

int cherche(int tab[], int taille, int n) {
  int i = 0;
  int res = 0;
  while (i < taille) {
    if (tab[i] == n) {
      res = 1;
    }
    i = i+1;
  }
  return res;
}

//int main(int argc, char *argv[]) {
//  int tab[] = {0,1,2,3};
//  int taille = 4;
//  int n = 5;
//  int res = cherche(tab, taille, n);
//  printf("%d\n", res);
//}

int dichotomie(int tab[], int taille, int n) {
  int a = 0;
  int b = taille;
  int moy = 0;
  //  int res = 0;
  while (b-a != 1) {
    moy = (b-a)/2;
      if (n < tab[moy]) {
	b = moy;
      } else {
	a = moy;
      }
  }
  return tab[moy];
}

//int main(int argc, char *argv[]) {
//  int tab[] = {1,2,3,4,5,6,7,8,9,10};
//  int taille = 10;
//  int n = 3;
//  int res = dichotomie(tab, taille, n);
//  printf("%d\n", res);
//}





