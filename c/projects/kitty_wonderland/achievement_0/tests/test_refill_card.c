#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <board.h>
#include <player.h>
#include <card.h>

struct board game;
struct player players[NUMBER_OF_PLAYERS_MAX];

void test_refill_card() {
  refill_card(&players[0], KITTY_STEAL, 0);
  if (players[0].hand[0] != KITTY_STEAL) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main(){
  srand(time(NULL));
  test_refill_card();
  return EXIT_SUCCESS;
}
