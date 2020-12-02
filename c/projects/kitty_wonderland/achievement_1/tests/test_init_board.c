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

void test_init_board() {
  init_board(NUMBER_OF_PLAYERS_MAX, &game, players, decks);
  for (int i = 0; i < NUMBER_OF_PLAYERS_MAX; ++i) {
    if (game.number_of_players != NUMBER_OF_PLAYERS_MAX) {
      printf("%s, %d\n", __FILE__, __LINE__);
      exit(1);
    }
    if (game.player_list[i] != &players[i]) {
      printf("%s, %d\n", __FILE__, __LINE__);
      exit(1);
    }
  }
}

int main(){
  srand(time(NULL));
  test_init_board();
  return EXIT_SUCCESS;
}
