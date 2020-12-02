#ifndef SET_GRAPH_H
#define SET_GRAPH_H

#include <server.h>
#include <graph.h>
#include <player.h>
#include <nodes.h>

struct graph {
  struct tile *tiles[NUMBER_OF_CARDS];
  int number_of_tiles;
};

struct graph* init_graph();
void free_graph(struct graph*);
boolean match_card(struct graph *g, struct tile *t);
int is_playable(struct graph*, enum card_id card); 

struct tile *find_tile(struct graph *g, struct position const *p);
struct position neighbour_position(struct position *p, enum direction d);
struct tile *compute_neighbour(struct graph *g, struct tile *t, enum direction d);
boolean is_connectable(struct graph *g, struct tile *t);

boolean valid_move_card(struct graph *g, struct move *m);
boolean valid_move_meeple(struct graph *g, struct move *m, struct player *p);
boolean valid_move(struct graph *g, struct move *m, struct player *p);

void add_card_connection(struct graph *g, struct tile *t);
void remove_card_connection(struct graph *g, struct tile *t);

int add_tail_tile(struct graph*, struct move const *m);
int remove_tail_tile(struct graph *g);

int add_meeple_in_graph(struct graph *g, struct move const *m);
//enum place place_meeple(enum place p, enum direction d);

#endif

