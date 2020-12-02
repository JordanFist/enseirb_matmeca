#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "player.h"

//Initializing a player
void init_player(struct player* p, struct deck d[], struct location l[], int grid[GRID_SIZE][GRID_SIZE]) {
  init_position_player(p, l, grid);
  p->deck = &d[p->id];
  init_deck(p->deck);
  p->life = STARTING_LIFE;
  p->mana = STARTING_MANA;
  p->gain = STARTING_GAIN;
  for (int i = 0; i < NUMBER_OF_CARD_IN_HAND; ++i)
    p->hand[i] = &d[p->id].player_deck[i];
}

//Initializing the player position
void init_position_player(struct player* p, struct location l[], int grid[GRID_SIZE][GRID_SIZE]) {
  p->coordinate = &l[p->id];
  int x,y;
  do {
    x = rand() % GRID_SIZE;
    y = rand() % GRID_SIZE;
  } while (grid[x][y] != EMPTY);
  grid[x][y] = PLAYER;
  p->coordinate->new.x = x;
  p->coordinate->new.y = y;
}

//Displaying player informations
void display_player_information(struct player* p) {
  printf("player life : %d\n", p->life);
  printf("player mana : %d\n", p->mana);
  printf("player gain : %d\n", p->gain);
  printf("player hand : ");
  for (int i = 0; i < NUMBER_OF_CARD_IN_HAND; ++i) {
    display_card_name(p->hand[i][0]);
    printf("/");
  }
}

//Checking if a player is alive
int is_alive(struct player* p) {
  return (p->life > 0);
}

//Giving the card position in the player hand, if the player can play a card 
int select_card(struct player *p) {
  int tab[NUMBER_OF_CARD_IN_HAND] = {};
  int res = 0;
  for (int i = 0; i < NUMBER_OF_CARD_IN_HAND; ++i) {
    if (p->mana >= card_mana(p->hand[i][0])) {
      tab[res] = i;
      ++res;
    }
  }
  if (res == 0)
    return -1;
  int x = rand() % res;
  return tab[x];
}

//Applying the card chosen on a player
void apply_card(struct player* p, struct player* t, enum card c, int grid[GRID_SIZE][GRID_SIZE]) {
  int ran;
  int x = t->coordinate->new.x;
  int y = t->coordinate->new.y;
  struct coord coord[] = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
  switch(c) {
  case (KITTY_THINK):
    p->mana -= 5;
    if (p->gain < INT_MAX)
      p->gain += 1;
    break;
  case (KITTY_STEAL):
    p->mana -= 10;
    if (p->gain < INT_MAX)
      p->gain += 1;
    if (t->gain > 1)
      t->gain -= 1;
    break;
  case (KITTY_PANACEA):
    p->mana -= 2;
    if (p->life < INT_MAX - 10)
      p->life += 10;
    break;
  case (KITTY_RAZOR):
    p->mana -= 2;
    t->life -= 10;
    if (t->life <= 0)
      dead(t, grid);
    break;
  case (KITTY_HELL_IS_OTHERS):
    p->mana -= 100;
    t->life -= INT_MAX;
    if (t->life <= 0)
      dead(t, grid);
    break;
  case (KITTY_STONE):
    do {
      ran = rand() % 4;
    } while (grid[coord[ran].x][coord[ran].y] != EMPTY);
    grid[coord[ran].x][coord[ran].y] = CANDY;
    break;
  default:
    exit(1);
    break;
  }
}

//Checking is the player is sticky
int is_sticky(struct player* p, int grid[GRID_SIZE][GRID_SIZE]) {
  int x = p->coordinate->new.x;
  int y = p->coordinate->new.y;
  if (grid[x + 1][y] == CANDY && grid[x - 1][y] == CANDY && grid[x][y + 1] == CANDY && grid[x][y - 1] == CANDY)
    return 1;
  return 0;
}

//Killing the player
void dead(struct player* p, int grid[GRID_SIZE][GRID_SIZE]) {
  p->life = 0;
  grid[p->coordinate->new.x][p->coordinate->new.y] = EMPTY; 
}

