#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <board.h>
#include <player.h>
#include <card.h>
#include <position.h>

struct board game;
struct player players[NUMBER_OF_PLAYERS_MAX];
struct deck decks[NUMBER_OF_PLAYERS_MAX];
struct location locations[NUMBER_OF_PLAYERS_MAX];
int grid[GRID_SIZE][GRID_SIZE];

void test_init_position_player() {
  init_position_player(&players[0], locations, grid);
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      if (grid[j][i] == PLAYER) {
	if (locations[0].new.x != j && locations[0].new.y != i) {
	  printf("%s, %d %d\n", __FILE__, __LINE__, i);
	  exit(1);
	}
      }
    }
  }
}

int main() {
  srand(time(NULL));
  init_grid(grid);
  test_init_position_player();
  return EXIT_SUCCESS;
}
