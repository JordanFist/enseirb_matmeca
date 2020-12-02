#include <stdio.h>
#include <stdlib.h>
#include <set_graph.h>

struct graph* init_graph() {
  struct graph *g = (struct graph *) malloc(sizeof(struct graph));
  if (g == NULL)
    exit(1);
  g->number_of_tiles = 0;
  return g;
}

struct tile *find_tile(struct graph *g, struct position const *p) {
  for (int i = 0; i < g->number_of_tiles; ++i) {
    if (g->tiles[i]->pos.x == p->x && g->tiles[i]->pos.y == p->y)
      return g->tiles[i];
  }
  return NULL;
}

struct position neighbour_position(struct position *p, enum direction d) {
  struct position pos = {p->x, p->y};
  if (d == NORTH) 
    ++pos.y;
  if (d == WEST) 
    --pos.x;
  if (d == SOUTH) 
    --pos.y;
  if (d == EAST) 
    ++pos.x;
  return pos;
}

struct tile *compute_neighbour(struct graph *g, struct tile *t, enum direction d) {
  struct position pos = neighbour_position(&t->pos, d);
  return find_tile(g, &pos);
}    

boolean match_card(struct graph *g, struct tile *t) {
  int cpt = 0;
  for (int i = 0; i < SIDES; ++i) {
    if (match_side(t, compute_neighbour(g, t, i), i) == TRUE) {
      ++cpt;
    }
  }
  if (cpt == SIDES)
    return TRUE;
  return FALSE;
}

boolean is_connectable(struct graph *g, struct tile *t) {
  for (int i = 0; i < SIDES; ++i) {
    if (match_card(g, t) == TRUE) {
      t->orientation = i;
      return TRUE;
    }
    rotation(t, WEST);
  }
  return FALSE;
}

//fonction qui verifie que la carte est jouable quelque part sur le graphe
boolean is_playable(struct graph* g, enum card_id card) {
  struct position pos = {0, 0};
  struct tile *tile = init_tile(card, NORTH, pos);
  for (int i = 0 ; i < g->number_of_tiles ; i++) {
    for (int j = 0; j < NEIGHBOUR_CARDS; j++) {
      tile->pos = neighbour_position(&g->tiles[i]->pos, j);
      if((is_empty_tile(compute_neighbour(g, g->tiles[i], j)) == TRUE) && (is_connectable(g, tile) == TRUE)) {
	free_tile(tile);
	return TRUE;
      }
    }
  }
  free_tile(tile);
  return FALSE;
}

boolean valid_move_card(struct graph *g, struct move *m) {
  struct tile *t = init_tile(m->card, m->dir, m->onto);
  if (match_card (g, t) == TRUE) {
    free_tile(t);
    return TRUE;
  }
  free_tile(t);
  return FALSE;
}

boolean valid_move_meeple(struct graph *g, struct move *m, struct player *p) {
  m->check = VALID;
  add_tail_tile(g, m);
  if (m->place != NO_MEEPLE) {
    if (p->number_of_meeples > 0)
      --p->number_of_meeples;
    else {
      remove_tail_tile(g);
      m->check = FAILED;
      return FALSE;
    }
    if (is_meeple_in_area(g->tiles[g->number_of_tiles - 1]->nodes[m->place]) == FALSE) {
      remove_tail_tile(g);
      m->check = FAILED;
      return TRUE;
    }
    remove_tail_tile(g);
    m->check = FAILED;
    return FALSE;
  }
  remove_tail_tile(g);
  m->check = FAILED;
  return TRUE;
}

boolean valid_move(struct graph *g, struct move *m, struct player *p) {
  if (valid_move_card(g, m) == TRUE && valid_move_meeple(g, m, p) == TRUE) {
    m->check = VALID;
    return TRUE;
  }
  m->check = FAILED;
  return FALSE;
}

int add_meeple_in_graph(struct graph *g, struct move const *m) {
  if (m->place != NO_MEEPLE) {
    struct tile *t = find_tile(g, &m->onto);
    if (t != NULL) {
      t->nodes[m->place]->meeple = TRUE;
      t->nodes[m->place]->meeple_owner = m->player;
    }
  }
  return EXIT_SUCCESS;
}


int add_tail_tile(struct graph *g, struct move const *m) {
  struct tile *tile_add = init_tile(m->card, m->dir, m->onto);
  if (m->check == VALID) {
    g->tiles[g->number_of_tiles] = tile_add;
    ++g->number_of_tiles;
    add_card_connection(g, tile_add);
    return EXIT_SUCCESS; 
  } 
  free_tile(tile_add);
  return EXIT_FAILURE;
}

int remove_tail_tile(struct graph *g) {
  struct tile *t_remove = g->tiles[g->number_of_tiles - 1];
  if (t_remove != NULL) {
    remove_card_connection(g, t_remove);
    free_tile(t_remove);
    --g->number_of_tiles;
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

void remove_card_connection(struct graph *g, struct tile *t) {
  struct tile *t_neighbour;
  for (int i = 0; i < NEIGHBOUR_CARDS; ++i) {
    t_neighbour = compute_neighbour(g, t, i);
    for (int j = (CONNEXIONS_PER_SIDE-1) * i; j < (CONNEXIONS_PER_SIDE-1) * (i + 1); ++j) {
      if (t_neighbour != NULL)
	node_disconnection(t->nodes[j], t_neighbour->nodes[opposite_node(j)]);
    }
  }
}

void add_card_connection(struct graph *g, struct tile *t) {
  struct tile *t_neighbour;
  for (int i = 0; i < NEIGHBOUR_CARDS; ++i) {
    t_neighbour = compute_neighbour(g, t, i);
    for (int j = (CONNEXIONS_PER_SIDE-1) * i; j < (CONNEXIONS_PER_SIDE-1) * (i + 1); ++j) {
      if (t_neighbour != NULL)
	node_connection(t->nodes[j], t_neighbour->nodes[opposite_node(j)]);
    }
  }
}

void free_graph(struct graph *g) {
  for (int i = 0; i < g->number_of_tiles; ++i)
    free_tile(g->tiles[i]);
  free(g);
}



