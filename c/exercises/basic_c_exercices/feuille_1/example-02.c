#include <stdio.h>
int mod(int a, int b) {
  return a%b;
}

int pgcd_rec(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return pgcd_rec(b, mod(a,b));
  }
}

int tab_premier(int n,int tab[]) {
  tab[0]=0;
  int i=0;
    while (i<=n) {
      tab[i+1]=tab[i]+2;
      i = i + 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
  int n=10;
  int tab[n];
  tab_premier(n,tab);
  int i=0;
   while (i<=n) {
      printf("%d\n", tab[i]);
      i = i + 1;
   }
}
  



//int main(int argc, char *argv[]) {
//  int tab[] = {10,20,30,40,50};
//  int i=0;
//  while (i<=4) {
//    printf("%d\n", tab[i]);
//    i = i + 1;
//  }
//}

//int main(int argc, char *argv[]) {  
//  int res = pgcd_rec(15,3);
//  printf("%d\n", res);
//  return 0;
//}

