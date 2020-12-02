#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "deck.h"
#include "card.h"

#define STARTING_LIFE 50
#define STARTING_MANA 0
#define STARTING_GAIN 1
#define DISPLACEMENT_MAX 5
#define MAX_MOV 5
struct player {
  int id;
  int life;
  int mana;
  int gain;
  struct deck* deck;
  enum card* hand[NUMBER_OF_CARD_IN_HAND];
  struct location* coordinate;
};

void init_player(struct player p[], struct deck d[], struct location l[], int grid[GRID_SIZE][GRID_SIZE]);
void init_position_player(struct player* p, struct location l[], int grid[GRID_SIZE][GRID_SIZE]);
void display_player_information(struct player* p);
int is_alive(struct player* p);
int select_card(struct player *p);
void apply_card(struct player* p, struct player* t, enum card c, int grid[GRID_SIZE][GRID_SIZE]);
int is_sticky(struct player* p, int grid[GRID_SIZE][GRID_SIZE]);
void dead(struct player* p, int grid[GRID_SIZE][GRID_SIZE]);

#endif
