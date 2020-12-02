#ifndef DECK_H
#define DECK_H

#include "card.h"

#define NUMBER_OF_CARD_IN_DECK 50

struct deck {
  int deck_position;
  enum card player_deck[NUMBER_OF_CARD_IN_DECK];
};

void init_deck(struct deck* d);
void refill_card(struct deck* d, int position);
void shuffle(struct deck* d, int all_shuffle);

#endif

