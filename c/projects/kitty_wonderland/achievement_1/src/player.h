#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"
#include "card.h"

#define STARTING_LIFE 50
#define STARTING_MANA 0
#define STARTING_GAIN 1

struct player {
  int id;
  int life;
  int mana;
  int gain;
  struct deck* deck;
  enum card* hand[NUMBER_OF_CARD];
};

void init_player(struct player p[], struct deck d[]);
void display_player_information(struct player* p);
int is_alive(struct player* p);
int select_card(struct player *p);
void apply_card(struct player* p, struct player* t, enum card c);

#endif
