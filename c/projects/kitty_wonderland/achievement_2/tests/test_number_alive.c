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

void test_number_alive() {
  if (number_alive(&game) != NUMBER_OF_PLAYERS_MAX) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main(){
  srand(time(NULL));
  init_grid(grid);
  init_board(NUMBER_OF_PLAYERS_MAX, &game, players, decks, locations, grid);
  test_number_alive();
  return EXIT_SUCCESS;
}
