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

void test_move () {
  locations[0].new.x = 25;
  locations[0].new.y = 25;
  int x = locations[0].new.x;
  int y = locations[0].new.y;
  grid[x][y + 1] = CANDY;
  grid[x][y - 1] = CANDY;
  grid[x - 1][y] = CANDY;
  grid[x + 1][y] = CANDY;
  
  move(&locations[0], grid);
  if (locations[0].new.x != 25 && locations[0].new.y != 25) {
    printf("%s : %d", __FILE__, __LINE__);
    exit(1);
  }
  init_grid(grid);
  move(&locations[0], grid);
  if (grid[locations[0].old.x][locations[0].old.y] != EMPTY) {
    printf("%s : %d", __FILE__, __LINE__);
    exit(1);
  }
  if (grid[locations[0].new.x][locations[0].new.y] != PLAYER) {
    printf("%s : %d", __FILE__, __LINE__);
    exit(1);
  }
}
  
int main(int argc, char *argv[]) {
  init_grid(grid);
  test_move();
  return EXIT_SUCCESS;
}
