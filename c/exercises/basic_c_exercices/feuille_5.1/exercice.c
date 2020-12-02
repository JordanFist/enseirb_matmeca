#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct voiture {
  int cv;
  int mes;
  int co2;
  char matricule[64];
  char proprio[64];
  int departement;
};

void affiche_voiture(struct voiture v) {
  printf("%s %d %dcv (%dgr/km): %s (%d)\n", v.matricule, v.mes, v.cv, v.co2, v.proprio, v.departement);
}

/*
int main(int argc, char *argv[]) {
  struct voiture my_car = {190, 2008, 203, "AA-XXX-AA", "MORANDAT", 33};
  affiche_voiture(my_car);
  return 0;
}
*/

void affiche(int len, struct voiture v[]) {
  for(int i = 0; i < len; ++i) {
    if (v[i].mes > 2014)
      printf("%s %d %dcv (%dgr/km): %s (%d)\n", v[i].matricule, v[i].mes, v[i].cv, v[i].co2, v[i].proprio, v[i].departement);
  }
}

/*
int main(int argc, char *argv[]) {
  struct voiture my_car = {190, 2008, 203, "AA-XXX-AA", "MORANDAT", 33};
  struct voiture my_car_2 = {200, 2015, 250, "BB-XXX-BB", "SANDRI", 13};
  struct voiture my_car_3 = {150, 2016, 199, "CC-XXX-CC", "SANDRI", 13};
  struct voiture mes_voitures[] = {my_car, my_car_2, my_car_3};
  int len = 3;
  affiche (len, mes_voitures);
  return 0;
}
*/

int temporaire(struct voiture v) {
  return ((v.matricule[0] == 'W') && (v.matricule[1] == 'W')); //comparaison de caractere avec ' et pas "
}

/*
int main(int argc, char *argv[]) {
  struct voiture my_car = {190, 2008, 203, "WW-XXX-AA", "MORANDAT", 33};
  struct voiture my_car_2 = {200, 2015, 250, "BB-XXX-BB", "SANDRI", 13};
  temporaire(my_car);
  return 0;
}
*/

void affiche_temporaire(int len, struct voiture v[]) {
  for(int i = 0; i < len; ++i) {
    if (temporaire(v[i]) == 1)
      printf("%s %d %dcv (%dgr/km): %s (%d)\n", v[i].matricule, v[i].mes, v[i].cv, v[i].co2, v[i].proprio, v[i].departement);
  }
}

/*
int main(int argc, char*argv[]) {
  int len = 2;
  struct voiture my_car = {190, 2008, 203, "WW-XXX-AA", "MORANDAT", 33};
  struct voiture my_car_2 = {200, 2015, 250, "BB-XXX-BB", "SANDRI", 13};
  struct voiture mes_voitures[] = {my_car, my_car_2};
  affiche_temporaire(len, mes_voitures);
  return 0;
}
*/

void matriculer(struct voiture *v, char *immatriculation) {
  if (temporaire(*v) == 1) 
    strcpy((*v).matricule,immatriculation);
}

/*
int main(int argc, char *argv[]) {
  struct voiture my_car = {190, 2008, 203, "WW-XXX-AA", "MORANDAT", 33};
  //struct voiture my_car_2 = {200, 2015, 250, "BB-XXX-BB", "SANDRI", 13};
  matriculer(&my_car, "AA-XXX-AA");
  printf("%s\n", my_car.matricule);
  return 0;
}
*/

/*
double puissance_fiscale(struct voiture v) {
    return (double) v.co2/45 + pow((0.736 * v.cv) / 40,1.6);
}
*/

/*
int main(int argc, char *argv[]) {
  struct voiture my_car = {190, 2008, 203, "WW-XXX-AA", "MORANDAT", 33};
  double res = puissance_fiscale(my_car);
  printf("%f\n", res);
  return 0;
}
*/


void prochaine_immatriculation(char *immatriculation, char alphabet[], char chiffre[]) {
  if (immatriculation[5] != chiffre[9])
    immatriculation[5] = chiffre[immatriculation[5] + 1];
//printf("%c\n", immatriculation[5] + 1);      
}



int main(int argc, char *argv[]) {
  char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'X', 'Y', 'Z'};
  char chiffre[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  prochaine_immatriculation("AA-123-AA", alphabet, chiffre);
  return 0;
}
