#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <board.h>
#include <player.h>
#include <deck.h>
#include <card.h>
#include <position.h>

struct board game;
struct player players[NUMBER_OF_PLAYERS_MAX];
struct deck decks[NUMBER_OF_PLAYERS_MAX];
struct location locations[NUMBER_OF_PLAYERS_MAX];
int grid[GRID_SIZE][GRID_SIZE];

void test_reachable () {
  locations[0].new.x = 25;
  locations[0].new.y = 25;
  int x = locations[0].new.x;
  int y = locations[0].new.y;
  grid[x][y + 1] = CANDY;
  grid[x][y - 1] = CANDY;
  grid[x - 1][y] = CANDY;
  grid[x + 1][y] = CANDY;
  struct coord spots = {27, 28};
  int res = reachable(&locations[0].new, &spots, grid);
  if (res != 0) {
    printf("%s : %d", __FILE__, __LINE__);
    exit(1);
  }
  init_grid(grid);

  if (res != 1) {
    printf("%s : %d", __FILE__, __LINE__);
    exit(1);
  }
}
  
int main(int argc, char *argv[]) {
  init_grid(grid);
  init_board(2, &game, players, decks, locations, grid);
  //test_reachable();
  return EXIT_SUCCESS;
}
