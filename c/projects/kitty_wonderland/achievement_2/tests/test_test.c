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

void test_test () {
  
  struct coord c = {2, 2};
  struct coord spots = {2, 2};
  int path[] = {0, 1, 2, 3, 4};
  grid[c.x][c.y] = PLAYER;
  int res = test(&c, &spots, path, grid);
  if (res != 1) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (grid[spots.x][spots.y] != CONFLICT) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
  grid[spots.x][spots.y] = EMPTY;
  
  
  struct coord c_2 = {1,1};
  struct coord spots_2 = {49,49};
  int path_2[] = {4, 1, 0, 1, 4};
  grid[c_2.x][c_2.y] = PLAYER;
  res = test(&c_2, &spots_2, path_2, grid);
  if (res != 1) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (grid[spots_2.x][spots_2.y] != EMPTY) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}
  
int main(int argc, char *argv[]) {
  init_grid(grid);
  test_test();
  return EXIT_SUCCESS;
}
