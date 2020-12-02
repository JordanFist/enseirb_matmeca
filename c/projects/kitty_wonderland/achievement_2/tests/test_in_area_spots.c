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

void test_in_area_spots () {
  struct coord c = {1, 1};
  struct coord verif[] = {{1, 1}, {0, 0}, {49, 0}, {0, 49}, {49,49}, {48,49}, {0,1}, {3,2}, {1,4}, {48,1}};
  struct coord spots[AVAILABLE_SPOTS] = {};
  in_area_spots(&c, spots);
  int stop = 0;
  for (int j = 0; j < 10; ++j) {
    for (int i = 0; i < AVAILABLE_SPOTS; ++i) {
      if ((verif[j].x == spots[i].x) && (verif[j].y == spots[i].y)) {
	++stop;
      }
    }
  }
  if (stop != 10) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}
  
int main(int argc, char *argv[]) {
  init_grid(grid);
  init_board(2, &game, players, decks, locations, grid);
  test_in_area_spots();
  return EXIT_SUCCESS;
}
