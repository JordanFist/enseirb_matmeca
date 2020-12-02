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

void test_refill_card() {
  int position = 2;
  int x = decks[0].player_deck[position];
  int y = decks[0].player_deck[decks[0].deck_position];
  refill_card(decks, position);
  decks[0].deck_position = 5;
  if (decks[0].player_deck[position] != y) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  if (decks[0].player_deck[decks[0].deck_position] != x) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
  decks[0].deck_position = NUMBER_OF_CARD_IN_DECK - 1;
  refill_card(decks, position);
  if (decks[0].deck_position != 5) {
    printf("%s , %d\n", __FILE__, __LINE__);
    exit(1);
  }
}

int main(){
  init_board(2, &game, players, decks);
  srand(time(NULL));
  test_refill_card();
  return EXIT_SUCCESS;
}

