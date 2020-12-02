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

void test_is_alive() {
  players[0].life = 10;
  if (is_alive(&players[0]) != 1) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  
  players[0].life = 0;
  if (is_alive(&players[0]) != 0) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  
  players[0].life = -2;
  if (is_alive(&players[0]) != 0) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main(){
  srand(time(NULL));
  test_is_alive();
  return EXIT_SUCCESS;
}
