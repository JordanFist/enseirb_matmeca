#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"

#define STARTING_LIFE 50
#define STARTING_MANA 0
#define STARTING_GAIN 1

struct player {
  int id;
  int life;
  int mana;
  int gain;
  enum card hand[NUMBER_OF_CARD];
};

void init_player(struct player p[]);
void display_player_information(struct player* p);
int is_alive(struct player* p);
int select_card(struct player *p);
void refill_card(struct player* p, enum card c, int position);
void apply_card(struct player* p, struct player* t, enum card c);

#endif
