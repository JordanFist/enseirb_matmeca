#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <board.h>
#include <player.h>
#include <card.h>

struct board game;
struct player players[NUMBER_OF_PLAYERS_MAX];

void test_random_card() {
  int tab[NUMBER_OF_CARD_IN_HAND] = {};
  for (int i = 0; i < 1310; ++i) {
    switch(random_card()) {
    case(KITTY_THINK):
      ++tab[KITTY_THINK];
      break;
    case(KITTY_STEAL):
      ++tab[KITTY_STEAL];
      break;
    case(KITTY_PANACEA):
      ++tab[KITTY_PANACEA];
      break;
    case(KITTY_RAZOR):
      ++tab[KITTY_RAZOR];
      break;
    case(KITTY_HELL_IS_OTHERS):
      ++tab[KITTY_HELL_IS_OTHERS];
      break;
    default:
      printf("%s : %d\n", __FILE__, __LINE__);
      exit(1);
      break;
    }
  }
  for (int i = 0; i < NUMBER_OF_CARD_IN_HAND; ++i) {
    if (tab[i] == 0) {
      printf("%s : %d\n", __FILE__, __LINE__);
      exit(1);
    }
  }
}

int main() {
  srand(time(NULL));
  test_random_card();
  return EXIT_SUCCESS;
}
