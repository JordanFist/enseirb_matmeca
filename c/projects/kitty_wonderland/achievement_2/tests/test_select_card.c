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

int cost(struct player* p, int position) {
  if (p->mana >= card_mana(p->hand[position][0]))
    return 1;
  return 0;
}

void test_select_card() {
  players[0].mana = 0;
  if (select_card(&players[0]) != -1) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }

  players[0].mana = 2;
  int x = select_card(&players[0]);
  if (cost(&players[0], x) != 1 && cost(&players[0], x) != 1) { 
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  
  players[0].mana = 10;
  x = select_card(&players[0]);
  if (cost(&players[0], x) != 1 && cost(&players[0], x) != 1 && cost(&players[0], x) != 1 && cost(&players[0], x) != 1) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main() {
  srand(time(NULL));
  init_grid(grid);
  init_board(NUMBER_OF_PLAYERS_MAX, &game, players, decks, locations, grid);
  test_select_card();
  return EXIT_SUCCESS;
}
