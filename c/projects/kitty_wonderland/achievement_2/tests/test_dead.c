#include <stdlib.h>
#include <stdio.h>
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

void test_dead() {
  grid[locations[0].new.x][locations[0].new.y] = PLAYER;
  dead(&players[0],grid);
  if (players[0].life != 0) {
    printf("%s, %d", __FILE__, __LINE__);
    exit(1);
  }
  if (grid[locations[0].new.x][locations[0].new.y] != EMPTY) {
    printf("%s, %d", __FILE__, __LINE__);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  init_grid(grid);
  init_board(2, &game, players, decks, locations, grid);
  test_dead();
  return EXIT_SUCCESS;
}
