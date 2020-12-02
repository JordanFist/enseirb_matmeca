#ifndef PLAYER_H
#define PLAYER_H

#include <server.h>

#define STARTING_NUMBER_OF_MEEPLES 8

struct player {
  int id_player;
  struct player_base p;
  boolean player_alive;
  int number_of_meeples;
  int points;
};

struct players {
  struct player *players;
  int number_of_players;
};

struct players *init_players(int number_of_players);
int remaining_players(struct players *players);
unsigned int compute_next_player(struct players *players, struct player *player);
void eject_player(struct players *players, struct player *player);
void free_players(struct players *p);

#endif 
