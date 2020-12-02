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

void test_init_player() {
  init_player(&players[0], decks, locations, grid);
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
  if (players[0].deck != &decks[players[0].id]) {
    printf("%s, %d\n", __FILE__, __LINE__);
    exit(1);
  }
  for (int i = 0; i < NUMBER_OF_CARD_IN_HAND; ++i) {
    if (players[0].hand[i] != &decks[players[0].id].player_deck[i]) {
      printf("%s, %d %d\n", __FILE__, __LINE__, i);
      exit(1);
    }
  }
}

int main() {
  srand(time(NULL));
  init_grid(grid);
  test_init_player();
  return EXIT_SUCCESS;
}
