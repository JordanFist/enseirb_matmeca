#include <server.h>
#include <stdio.h>
#include <stdlib.h>
#include <set_graph.h>
#include <graph.h>
#include <set_dynamic.h>
#include <nodes.h>

#define STARTING_NUMBER_OF_MEEPLES 8

static struct graph *graph;

unsigned int identity;
static int number_of_meeples;
#define NO_PLAYER -1

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
char const *get_player_name() {
  char const *name = "Julien";
  return name;
}

boolean search_valid_position_meeple(struct graph *g, struct move *m) {
  struct tile *t = init_tile(m->card, NORTH, m->onto);
  struct node *n = t->nodes[m->place];
  rotation(t, m->dir);
  m->check = VALID;
  add_tail_tile(graph, m);
  struct node *n_check;
  struct set *stack = set__empty();
  struct set *visited = set__empty();
  if (set__find(visited, n) == FALSE) {
    set__add(stack, n);
    set__add(visited, n);
  }
  while (set__is_empty(stack) == FALSE) { 
    n_check = set__remove(stack);
    if (n_check != NULL && n_check->meeple == TRUE) {
      set__free(stack);
      set__free(visited);
      m->place = NO_MEEPLE;
      remove_tail_tile(graph);
      m->check = FAILED;
      return FALSE;
    }
    for (int i = 0; i < CONNEXIONS_PER_SIDE; ++i) {
      if (n_check->next_nodes[i] != NULL && set__find(visited, n_check->next_nodes[i]) == FALSE) {
	set__add(stack, n_check->next_nodes[i]);
	set__add(visited, n_check->next_nodes[i]);
      }
    }
  }
  set__free(stack);
  set__free(visited);
  remove_tail_tile(graph);
  m->check = FAILED;
  return TRUE;
}


struct move search_valid_position_card(struct graph *g, struct move *m) {
  struct tile *tile = init_tile(m->card, m->dir, m->onto);
  for (int i = 0 ; i < g->number_of_tiles; i++) {
    for (int j = 0; j < NEIGHBOUR_CARDS; j++) {
      tile->pos = neighbour_position(&g->tiles[i]->pos, j);
      if((is_empty_tile(compute_neighbour(g, g->tiles[i], j)) == TRUE) && (is_connectable(g, tile) == TRUE)) {
	m->onto = tile->pos;
	m->dir = tile->orientation;
	free_tile(tile);
	return *m;
      }
    }
  }
  free_tile(tile);
  return *m;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void initialize(unsigned int id, unsigned int n_players) {
  identity = id;
  number_of_meeples = STARTING_NUMBER_OF_MEEPLES;
  graph = init_graph();
  printf("Initialisation du client \n");
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
struct move play(enum card_id card, struct move const previous_moves[], size_t n_moves) {
  for (unsigned int i = 0; i < n_moves; ++i) {
    add_tail_tile(graph, &previous_moves[i]);
    add_meeple_in_graph(graph, &previous_moves[i]);
  }
  struct move m = {FAILED, identity, card, {0, 0}, NORTH, NO_MEEPLE};
  m = search_valid_position_card(graph, &m);
  
  int i = 0;
  if (number_of_meeples > 0) {
    while (allowed_positions[card][i] != NO_MEEPLE) {
      m.place = allowed_positions[card][i];
      if (search_valid_position_meeple(graph, &m) == TRUE) {
	--number_of_meeples;
	break;
      }
      ++i;
    }
  }
  return m; 
}

#pragma GCC diagnostic pop
void finalize(){
  printf("finalisation du jeu du client \n");
  free_graph(graph);
}
