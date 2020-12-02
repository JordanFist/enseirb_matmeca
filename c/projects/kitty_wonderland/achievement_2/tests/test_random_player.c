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

void test_random_player() {
  for (int k = 0; k < 10; k++) {
    int x = random_player(&game, game.player_list[0]);
    if (x == 0) {
      x = random_player(&game, game.player_list[0]);
      printf("%s : %d\n", __FILE__, __LINE__);
      exit(1);
    }
  }
}

int main(){
  srand(time(NULL));
  init_grid(grid);
  init_board(NUMBER_OF_PLAYERS_MAX, &game, players, decks, locations, grid);
  test_random_player();
  return EXIT_SUCCESS;
}
