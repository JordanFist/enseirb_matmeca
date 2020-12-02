#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <board.h>
#include <player.h>
#include <card.h>

struct board game;
struct player players[NUMBER_OF_PLAYERS_MAX];

void test_init_player() {
  init_player(&players[0]);
  if (players[0].life != STARTING_LIFE) {
    printf("%s, %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (players[0].gain != STARTING_GAIN) {
    printf("%s, %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (players[0].mana != STARTING_MANA) {
    printf("%s, %d\n", __FILE__, __LINE__);
    exit(1);
  }
  for (int i = 0; i < NUMBER_OF_CARD_IN_HAND; ++i) {
    if (players[0].hand[i] != KITTY_THINK && players[0].hand[i] != KITTY_STEAL && players[0].hand[i] != KITTY_PANACEA && players[0].hand[i] != KITTY_RAZOR  && players[0].hand[i] != KITTY_HELL_IS_OTHERS) {
      printf("%s, %d\n", __FILE__, __LINE__);
      exit(1);
    }
  }
}

int main() {
  srand(time(NULL));
  test_init_player();
  return EXIT_SUCCESS;
}
