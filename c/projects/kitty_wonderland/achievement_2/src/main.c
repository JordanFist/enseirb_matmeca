#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>

#include "card.h"
#include "deck.h"
#include "position.h"
#include "player.h"
#include "board.h"

#define NUMBER_OF_PLAYERS_IN_THE_GAME 4
#define ROUND_MAX 100000

int seed = 0;

int main_game() {

  int grid[GRID_SIZE][GRID_SIZE];
  struct board game;
  struct player players[NUMBER_OF_PLAYERS_MAX];
  struct deck decks[NUMBER_OF_PLAYERS_MAX];
  struct location locations[NUMBER_OF_PLAYERS_MAX];
  init_grid(grid);
  init_board(NUMBER_OF_PLAYERS_IN_THE_GAME, &game, players, decks, locations, grid);
  
  int position;
  int random;
  int round = 1;
  while (number_alive(&game) > 1) {
    for (int i = 0; i < game.number_of_players; ++i) {
      if (is_alive(&players[i]) == 1) {
	if (is_sticky(&players[i], grid) == 0) {
	  if (players[i].mana < INT_MAX - players[i].gain)
	    players[i].mana += players[i].gain;
	  move(&locations[i], grid);
	} else 
	  dead(&players[i], grid);
      }
    }
    resolved_conflict(&game, grid);
    for (int i = 0; i < game.number_of_players; ++i) {
      if (number_alive(&game) <= 1)
	break;
      if (players[i].life > 0) {
        position = select_card(&players[i]);
        if (position != -1) {
          random = random_player(&game, &players[i]);
          apply_card(&players[i], &players[random], players[i].hand[position][0], grid);
          refill_card(&decks[i], position);
        }
      }
    }
    printf("---------------------------------------Round %d-------------------------------------------\n", round);
    display_board_information(&game);
    display_grid(grid);
    ++round;
    if (round > ROUND_MAX) {
      struct player winner = players[0];
      for (int i = 0; i < game.number_of_players; ++i) {
	if (players[i].life > winner.life)
	  winner = players[i];
      }
      printf("Player_%d won : the game is too long\n", winner.id);
      return EXIT_SUCCESS;
    }
  }
  for (int i = 0; i < game.number_of_players; ++i) {
    if (is_alive(&players[i]) == 1) {
      printf("Player_%d won\n", players[i].id);
      return EXIT_SUCCESS;
    }
  }
  printf("Draw \n");
  return EXIT_SUCCESS;
}

void parse_opts(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "s:")) != -1) {
    switch (opt) {
    case 's':
      seed = atoi(optarg);
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-s seed] \n",
	      argv[0]);
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char *argv[]) {
  parse_opts(argc, argv);
  printf("Seed: %d\n", seed);
  srand(seed);
  return main_game();
}
