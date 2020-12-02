#ifndef _DECK_H
#define _DECK_H

#include <server.h>
 
struct deck {
  enum card_id tab[NUMBER_OF_CARDS];
  int next_card;
};

static const int effective[LAST_CARD] = {9, 3, 2, 1, 1, 3, 3, 8, 4, 5, 2, 3, 4, 2, 3, 2, 4, 3, 1, 2, 1, 1, 2, 3};

struct deck *init_deck();
void fill_deck(struct deck *d);
enum card_id draw_card(struct deck *d); //renvoyer la 1ere carte  diponible
void shuffle(struct deck *d);
void free_deck(struct deck* deck);
int deck_is_empty(struct deck *d);
void print_deck (struct deck* d);

#endif
