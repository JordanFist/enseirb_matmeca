#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <board.h>
#include <player.h>
#include <card.h>

struct board game;
struct player players[NUMBER_OF_PLAYERS_MAX];

void test_number_alive() {
  if (number_alive(&game) != NUMBER_OF_PLAYERS_MAX) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main(){
  srand(time(NULL));
  init_board(NUMBER_OF_PLAYERS_MAX, &game, players);
  test_number_alive();
  return EXIT_SUCCESS;
}
