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

void test_apply_card_think() {
  apply_card(&players[0], &players[1], KITTY_THINK, grid);
  if (players[0].gain != 2) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

void test_apply_card_steal() {
  players[0].gain = STARTING_GAIN;
  apply_card(&players[0], &players[1], KITTY_STEAL, grid);
  if (players[0].gain != 2) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (players[1].gain != 1) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

void test_apply_card_panacea() {
  players[0].life = STARTING_LIFE;
  apply_card(&players[0], &players[1], KITTY_PANACEA, grid);
  if (players[0].life != 60) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

void test_apply_card_razor() {
  players[1].life = STARTING_LIFE;
  apply_card(&players[0], &players[1], KITTY_RAZOR, grid);
  if (players[1].life != 40) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

void test_apply_card_hell_is_others() {
  players[1].life = STARTING_LIFE;
  apply_card(&players[0], &players[1], KITTY_HELL_IS_OTHERS, grid);
  if (players[1].life != 0) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

void test_apply_card_kitty_stone() {
  apply_card(&players[0], &players[1], KITTY_STONE, grid);
  int x = locations[1].new.x;
  int y = locations[1].new.y;
  if (grid[x][y + 1] != CANDY && grid[x][y - 1] != CANDY && grid[x - 1][y] != CANDY && grid[x + 1][y] != CANDY) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main() {
  srand(time(NULL));
  init_grid(grid);
  init_board(NUMBER_OF_PLAYERS_MAX, &game, players, decks, locations, grid);
  
  test_apply_card_think();
  test_apply_card_steal();
  test_apply_card_panacea();
  test_apply_card_panacea();
  test_apply_card_hell_is_others();
  test_apply_card_kitty_stone();
  
  return EXIT_SUCCESS;
}
