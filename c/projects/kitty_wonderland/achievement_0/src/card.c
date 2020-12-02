#include <stdio.h>
#include <stdlib.h>
#include "card.h"

void display_card_name(enum card c) {
  switch(c) {
  case (KITTY_THINK):
    printf("Kitty_Think ");
    break;
  case (KITTY_STEAL):
    printf("Kitty_Steal ");
    break;
  case (KITTY_PANACEA):
    printf("Kitty_Panacea ");
    break;
  case (KITTY_RAZOR):
    printf("Kitty_Razor ");
    break;
  case (KITTY_HELL_IS_OTHERS):
    printf("Kitty_Hell_Is_Others ");
    break;
  default:
    exit(1);
    break;
  }
}

int card_mana(enum card c) {
  switch(c) {
  case (KITTY_THINK):
    return 5;
    break;
  case (KITTY_STEAL):
    return 10;
    break;
  case (KITTY_PANACEA):
    return 2;
    break;
  case (KITTY_RAZOR):
    return 2;
    break;
  case (KITTY_HELL_IS_OTHERS):
    return 100;
    break;
  default:
    exit(1);
    break;
  }
}

int card_rarity(enum card c) {
  return 100/card_mana(c);
}

int sum_rarities(enum card c) {
  int sum = 0;
  for (int i = KITTY_THINK; i <= c; i++)
    sum += card_rarity(i);
  return sum;
}

int random_card() {
  int x = rand() % sum_rarities(NUMBER_OF_CARD - 1);
  for (int i = KITTY_THINK; i <= NUMBER_OF_CARD - 1; i++) {
    if (x < sum_rarities(i)) {
      return i;
    }
  }
  return -1;
}

