#ifndef CARD_H
#define CARD_H

#define NUMBER_OF_CARD 5
#define NUMBER_OF_CARD_IN_HAND 5

enum card {
  KITTY_THINK, KITTY_STEAL, KITTY_PANACEA, KITTY_RAZOR, KITTY_HELL_IS_OTHERS 
};

void display_card_name(enum card c);
int card_mana(enum card c);
int card_rarity(enum card c);
int sum_rarities(enum card c);
int random_card();

#endif
