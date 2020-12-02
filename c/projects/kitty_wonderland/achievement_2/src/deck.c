#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

//Initializing a deck
void init_deck(struct deck* d) {
  d->deck_position = 5;
  for (int i = 0; i < NUMBER_OF_CARD_IN_DECK; ++i)
    d->player_deck[i] = random_card();
}

//Giving a new a card in the hand of the player at the chosen position
void refill_card(struct deck* d, int position) {
  int swap = d->player_deck[position];
  d->player_deck[position] = d->player_deck[d->deck_position];
  d->player_deck[d->deck_position] = swap;
  if (d->deck_position == NUMBER_OF_CARD_IN_DECK - 1) {
    shuffle(d, 0);
    d->deck_position = 5;
  } else
    d->deck_position += 1;
}

//Shuffling hand and deck if all_shuffle = 1, else only the deck
void shuffle(struct deck* d, int all_shuffle) {
  all_shuffle = !all_shuffle;
  int x;
  int swap;
  for (int i = 5 * all_shuffle; i < NUMBER_OF_CARD_IN_DECK; ++i) {
    x = (rand() % (NUMBER_OF_CARD_IN_DECK - 5 * all_shuffle)) + 5 * all_shuffle;
    swap = d->player_deck[i];
    d->player_deck[i] = d->player_deck[x];
    d->player_deck[x] = swap;
  }
}
