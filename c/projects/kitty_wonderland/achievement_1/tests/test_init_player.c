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

void test_init_player() {
  players[0].id = 0;
  init_player(&players[0], &decks[0]);
  if (players[0].life != STARTING_LIFE) {
    printf("%s, %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (players[0].gain != STARTING_GAIN) {
    printf("%s, %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (players[0].mana != STARTING_MANA) {
    printf("%s, %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (players[0].deck != &decks[0]) {
    printf("%s, %d\n", __FILE__, __LINE__);
    exit(1);
  }
  for (int i = 0; i < NUMBER_OF_CARD; ++i) {
    if (players[0].hand[i] != &decks[0].player_deck[i]) {
      printf("%s, %d\n", __FILE__, __LINE__);
      exit(1);
    }
  }
}

int main(int argc, char *argv[]) {
  test_init_player();
  return EXIT_SUCCESS;
}
    
