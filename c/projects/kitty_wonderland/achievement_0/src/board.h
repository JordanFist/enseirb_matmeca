#ifndef BOARD_H
#define BOARD_H

#include "player.h"

#define NUMBER_OF_PLAYERS_MAX 10

struct board {
  int number_of_players;
  struct player *player_list[NUMBER_OF_PLAYERS_MAX];
};

void init_board(int player_count, struct board* b, struct player p[]);
void display_board_information(struct board* b);
int random_player(struct board* b, struct player* p);
int number_alive(struct board* b);

#endif
