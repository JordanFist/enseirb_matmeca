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

void test_init_deck() {
  init_deck(&decks[0]);
  if (decks[0].deck_position != 5) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  for (int i = 0; i < NUMBER_OF_CARD_IN_DECK; i++) {
    if (decks[0].player_deck[i] != 0 && decks[0].player_deck[i] != 1 && decks[0].player_deck[i] != 2 && decks[0].player_deck[i] != 3 && decks[0].player_deck[i] != 4) {
      printf("%s , %d\n", __FILE__, __LINE__);
      exit(1);
    }
  }
}

int main(int argc, char *argv[]) {
  test_init_deck();
  return EXIT_SUCCESS;
}
