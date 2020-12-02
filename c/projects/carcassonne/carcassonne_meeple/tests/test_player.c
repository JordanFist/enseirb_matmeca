#include "../src/player.h"
#include <assert.h>
#include <stdio.h>

#define NUMBER_OF_PLAYERS 3

/*POUR L'AFFICHAGE*/
char FAIL[]="\033[31;1mFAIL\033[0m";
char PASSED[]="\033[32;1mPASSED\033[0m";

void test_init_players() {
  printf("Test de test_init_players ");
  
  struct players *p = init_players(NUMBER_OF_PLAYERS);
  assert(p->number_of_players == NUMBER_OF_PLAYERS);
  for (int i = 0; i < NUMBER_OF_PLAYERS; ++i) {
    assert(p->players[i].id_player == i);
    assert(p->players[i].points == 0);
    assert(p->players[i].player_alive == TRUE);
    assert(p->players[i].number_of_meeples == STARTING_NUMBER_OF_MEEPLES);
  }
  free_players(p);

  printf("%s\n",PASSED);
}

void test_compute_next_player() {
  printf("Test de test_compute_next_player ");
  
  struct players *p1 = init_players(NUMBER_OF_PLAYERS);
  unsigned int x = compute_next_player(p1, &p1->players[0]);
  assert(x == 1);
  
  struct players *p2 = init_players(NUMBER_OF_PLAYERS);
  p2->players[1].player_alive = FALSE;
  x = compute_next_player(p2, &p2->players[0]);
  assert(x == 2);
  
  struct players *p3 = init_players(NUMBER_OF_PLAYERS);
  eject_player(p3, &p3->players[2]);
  x = compute_next_player(p3, &p3->players[1]);
  assert(x == 0);
  
  struct players *p4 = init_players(NUMBER_OF_PLAYERS);
  eject_player(p4, &p4->players[2]);
  eject_player(p4, &p4->players[0]);
  x = compute_next_player(p4, &p4->players[1]);
  assert(x == 1);

  struct players *p5 = init_players(NUMBER_OF_PLAYERS);
  x = compute_next_player(p5, &p5->players[2]);
  assert(x == 0);
  
  free_players(p1);
  free_players(p2);
  free_players(p3);
  free_players(p4);
  free_players(p5);
  
  printf("%s\n",PASSED);
}

void test_eject_player() {
  printf("Test de test_eject_player ");
  
  struct players *p = init_players(NUMBER_OF_PLAYERS);
  eject_player(p, &p->players[0]);
  assert(remaining_players(p) == NUMBER_OF_PLAYERS - 1);
  assert(p->players[0].player_alive == FALSE);

  free_players(p);
  
  printf("%s\n",PASSED);
}

int main() {
  test_init_players();
  test_compute_next_player();
  test_eject_player();
  
  return 0;
}
