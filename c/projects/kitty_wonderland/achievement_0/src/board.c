#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void init_board(int player_count, struct board* b, struct player* p) {
  b->number_of_players = player_count;
  for (int i = 0; i < player_count; ++i) {
    b->player_list[i] = &p[i];
    p[i].id = i;
    init_player(&p[i]);
  }
}

void display_board_information(struct board* b) {
  for (int i = 0; i < b->number_of_players; ++i) {
    printf("player name : player_%d\n", b->player_list[i]->id);
    display_player_information(b->player_list[i]);
    printf("\n\n");
  }
}

int random_player(struct board* b, struct player* p) {
  int x = rand() % b->number_of_players;
  while ((x == p->id) || (b->player_list[x]->life <= 0))
    x = rand() % b->number_of_players;
  return x;
}

int number_alive(struct board* b) {
  int res = 0;
  for (int i = 0; i < b->number_of_players; i++) {
    if (is_alive(b->player_list[i]) == 1)
      ++res;
  }
  return res;
}
