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

void test_init_deck() {
  init_deck(&decks[0]);
  if (decks[0].deck_position != 5) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  for (int i = 0; i < NUMBER_OF_CARD_IN_DECK; i++) {
    if (decks[0].player_deck[i] != KITTY_THINK && decks[0].player_deck[i] != KITTY_STEAL && decks[0].player_deck[i] != KITTY_PANACEA && decks[0].player_deck[i] != KITTY_RAZOR && decks[0].player_deck[i] != KITTY_HELL_IS_OTHERS && decks[0].player_deck[i] != KITTY_STONE) {
      printf("%s , %d\n", __FILE__, __LINE__);
      exit(1);
    }
  }
}

int main(){
  srand(time(NULL));
  test_init_deck();
  return EXIT_SUCCESS;
}
