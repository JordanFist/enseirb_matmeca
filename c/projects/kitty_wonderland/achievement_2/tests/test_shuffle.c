#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <board.h>
#include <player.h>
#include <card.h>

struct board game;
struct player players[NUMBER_OF_PLAYERS_MAX];
struct deck decks[NUMBER_OF_PLAYERS_MAX];
struct location locations[NUMBER_OF_PLAYERS_MAX];
int grid[GRID_SIZE][GRID_SIZE];

void test_shuffle() {
  int occur_avant[NUMBER_OF_CARD] = {};
  int occur_apres[NUMBER_OF_CARD] = {};
  int verif[NUMBER_OF_CARD_IN_DECK];
  int verif_2[NUMBER_OF_CARD_IN_DECK];

  for (int i = 0; i < NUMBER_OF_CARD_IN_DECK; ++i) {
    ++occur_avant[decks[0].player_deck[i]];
    verif[i] = decks[0].player_deck[i];
  }

  shuffle(&decks[0], 1);

  for (int i = 0; i < NUMBER_OF_CARD_IN_DECK; ++i) {
    ++occur_apres[decks[0].player_deck[i]];
    verif_2[i] = decks[0].player_deck[i];
  }

  for (int i = 0; i < NUMBER_OF_CARD; ++i) {
    if (occur_avant[i] != occur_apres[i]) {
      printf("%s , %d\n", __FILE__, __LINE__);
      exit(1);
    }
  }
  int res = 0;
  for (int i = 0; i < NUMBER_OF_CARD_IN_DECK; ++i) {
    if (verif[i] == verif_2[i])
      ++res;
  }
  if (res > 30) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main(){
  srand(time(NULL));
  init_deck(&decks[0]);
  test_shuffle();
  return EXIT_SUCCESS;
}

