#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "player.h"

void init_player(struct player* p) {
  p->life = STARTING_LIFE;
  p->mana = STARTING_MANA;
  p->gain = STARTING_GAIN;
  for (int i = 0; i < NUMBER_OF_CARD_IN_HAND; ++i) {
      p->hand[i] = random_card();
  }
}

void display_player_information(struct player* p) {
  printf("player life : %d\n", p->life);
  printf("player mana : %d\n", p->mana);
  printf("player gain : %d\n", p->gain);
  printf("player hand : ");
  for (int i = 0; i < NUMBER_OF_CARD_IN_HAND; ++i) {
    display_card_name(p->hand[i]);
    printf("/");
  }
}


int is_alive(struct player* p) {
  return (p->life > 0);
}

int select_card(struct player *p) {
  int tab[NUMBER_OF_CARD_IN_HAND] = {};
  int res = 0;
  for (int i = 0; i < NUMBER_OF_CARD_IN_HAND; ++i) {
    if (p->mana >= card_mana(p->hand[i])) {
      tab[res] = i;
      ++res;
    }
  }
  if (res == 0)
    return -1;
  int x = rand() % res;
  return tab[x];
}

void refill_card(struct player* p, enum card c, int position) {
  p->hand[position] = c;
}

void apply_card(struct player* p, struct player* t, enum card c) {
  switch(c) {
  case 0:
    p->mana -= 5;
    p->gain += 1;
    break;
  case 1:
    p->mana -= 10;
    p->gain += 1;
    if (t->gain > 1)
      t->gain -= 1;
    break;
  case 2:
    p->mana -= 2;
    p->life += 10;
    break;
  case 3:
    p->mana -= 2;
    t->life -= 10;
    break;
  case 4:
    p->mana -= 100;
    t->life -= INT_MAX;
    break;
  default:
    exit(1);
    break;
  }
}
