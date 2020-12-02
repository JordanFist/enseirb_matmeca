#ifndef NODES_H
#define NODES_H

#include <server.h>
#include <set_dynamic.h>

#define CONNEXIONS_PER_SIDE 4
#define NO_PLAYER -1

struct node {
  enum landscape land_type;
  boolean meeple;
  int meeple_owner;
  struct node *next_nodes[CONNEXIONS_PER_SIDE];
  int number_of_nodes;
};

struct node *init_node(enum card_id card, int i);
boolean equal_landscape_node(struct node *n1, struct node *n2);
enum landscape landscape_node(struct node *n);
int size_next_nodes(struct node *n);
enum place opposite_node(enum place p);
void node_connection(struct node *n1, struct node *n2);
void shift_left(struct node *n, int i);
void node_disconnection(struct node *n1, struct node *n2);
boolean is_meeple_in_area(struct node *n);
void free_node(struct node *n);

#endif
