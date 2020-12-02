#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <board.h>
#include <player.h>
#include <deck.h>
#include <card.h>

struct board game;
struct player players[NUMBER_OF_PLAYERS_MAX];
struct deck decks[NUMBER_OF_PLAYERS_MAX];
struct location locations[NUMBER_OF_PLAYERS_MAX];
int grid[GRID_SIZE][GRID_SIZE];

void test_init_grid() {
  init_grid(grid);
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
	if (grid[j][i] != EMPTY) {
	  printf("%s : %d\n",__FILE__, __LINE__);
	  exit(1);
	}
    }	   
  }
}

int main(int argc, char *argv[]) {
  test_init_grid();
  return EXIT_SUCCESS;
}
  
