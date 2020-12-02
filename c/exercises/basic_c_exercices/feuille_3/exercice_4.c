#include <stdio.h>
#include <stdlib.h>

int test(char grille[])
{
  for (int i = 0; i < 9; ++i) {
    if (grille[i] == '.')
      return 0;
  }
  return 1;
}

void afficher_grille(char grille[])
{
  for (int i = 0; i < 9; ++i) {
    printf("%c", grille[i]);
    if (i == 2 || i == 5 || i == 8)
      printf("\n");
  }
}

int fin(char grille[])
{
  if ((grille[0] == grille[1] && grille[1] == grille[2] && grille[0] != '.') || (grille[3] == grille[4] && grille[4] == grille[5] && grille[3] != '.') || (grille[6] == grille[7] && grille[7] == grille[8] && grille[6] != '.') || (grille[0] == grille[3] && grille[3] == grille[6] && grille[0] != '.') || (grille[1] == grille[4] && grille[4] == grille[7] && grille[1] != '.') || (grille[2] == grille[5] && grille[5] == grille[8] && grille[2] != '.') || (grille[0] == grille[4] && grille[4] == grille[8] && grille[0] != '.') || (grille[2] == grille[4] && grille[4] == grille[6] && grille[2] != '.')) 
    return 1;
  return 0;
}

void morpion()
{
  int joueur_1;
  int joueur_2;
  char grille[9] = {'.', '.', '.', '.', '.', '.', '.', '.', '.'};

  for (int i = 0; i < 5; ++i) {
    printf("Tour de joueur_1 ?\n");
    scanf("%d", &joueur_1);
    grille[joueur_1 - 1] = 'X';
    afficher_grille(grille);

    if(fin(grille) == 1) {
      printf("le joueur_1 a gagné\n");
      goto fin;
    }

    if (test(grille) == 1) {
      printf("match nul !\n");
    fin :
      printf("Voulez-vous réessayer ?\n");
      int reponse;
      scanf("%d", &reponse);
      if (reponse == 1)
	morpion();
      else if (reponse != 1)
	break;
    }

    printf("Tour de joueur_2 ?\n");
    scanf("%d", &joueur_2);
    grille[joueur_2 - 1] = 'O';
    afficher_grille(grille);

    if (fin(grille) == 1) {
      printf("le joueur_2 a gagné\n");
      goto fin;
    }
  }
}

int main(int argc, char *argv[])
{
  morpion();
  return 0;
}
