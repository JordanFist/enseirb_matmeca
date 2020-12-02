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

void test_resolved_conflict() {
  locations[0].new.x = 25;
  locations[0].new.y = 25;
  locations[1].new.x = 25;
  locations[1].new.y = 25;
  grid[25][25] = CONFLICT;

  resolved_conflict(&game, grid);
  if (grid[25][25] != EMPTY) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (locations[0].new.x != locations[0].old.x || locations[0].new.y != locations[0].old.y) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (locations[1].new.x != locations[1].old.x || locations[1].new.y != locations[1].old.y) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  init_grid(grid);
  init_board(2, &game, players, decks, locations, grid);
  test_resolved_conflict();
  return EXIT_SUCCESS;
}
