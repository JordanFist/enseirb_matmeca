#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

#include <board.h>
#include <player.h>
#include <card.h>

struct board game;
struct player players[NUMBER_OF_PLAYERS_MAX];

void test_apply_card_think() {
  apply_card(&players[0], &players[1], KITTY_THINK);
  if (players[0].gain != 2) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

void test_apply_card_steal() {
  players[0].gain = STARTING_GAIN;
  apply_card(&players[0], &players[1], KITTY_STEAL);
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
  apply_card(&players[0], &players[1], KITTY_PANACEA);
  if (players[0].life != 60) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

void test_apply_card_razor() {
  players[1].life = STARTING_LIFE;
  apply_card(&players[0], &players[1], KITTY_RAZOR);
  if (players[1].life != 40) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

void test_apply_card_hell_is_others() {
  players[1].life = STARTING_LIFE;
  apply_card(&players[0], &players[1], KITTY_HELL_IS_OTHERS);
  if (players[1].life != -INT_MAX + STARTING_LIFE) {
    printf("%s : %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main() {
  srand(time(NULL));
  init_board(NUMBER_OF_PLAYERS_MAX, &game, players);
  
  test_apply_card_think();
  test_apply_card_steal();
  test_apply_card_panacea();
  test_apply_card_panacea();
  test_apply_card_hell_is_others();
  
  return EXIT_SUCCESS;
}
