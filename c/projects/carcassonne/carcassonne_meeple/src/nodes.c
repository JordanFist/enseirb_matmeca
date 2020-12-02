#include <nodes.h>
#include <server.h>
#include <stdio.h>
#include <stdlib.h>
#include <set_dynamic.h>

struct node *init_node(enum card_id card, int i) {
  struct node *n = (struct node *) malloc(sizeof(struct node));
  if (n == NULL)
    exit(1);
  n->land_type = cards_content[card][i];
  n->meeple = FALSE;
  n->meeple_owner = NO_PLAYER;
  n->number_of_nodes = 0;
  for (int i = 0; i < CONNEXIONS_PER_SIDE; ++i)
    n->next_nodes[i] = NULL;
  return n;
}

enum landscape landscape_node(struct node *n) {
  return n->land_type;
}

boolean  equal_landscape_node(struct node *n1, struct node *n2) {
  return (n1->land_type == n2->land_type);
}

int size_next_nodes(struct node *n) {
  return n->number_of_nodes;
}

enum place opposite_node(enum place p) {
  switch(p) {
  case(POS_NORTH_EAST): {
    return POS_SOUTH_EAST;
    break;
  }
  case(POS_NORTH): {
    return POS_SOUTH;
    break;
  }
  case(POS_NORTH_WEST): {
    return POS_SOUTH_WEST;
    break;
  }
  case(POS_WEST_NORTH): {
    return POS_EAST_NORTH;
    break;
  }
  case(POS_WEST): {
    return POS_EAST;
    break;
  }
  case(POS_WEST_SOUTH): {
    return POS_EAST_SOUTH;
    break;
  }
  case(POS_SOUTH_WEST): {
    return POS_NORTH_WEST;
    break;
  }
  case(POS_SOUTH): {
    return POS_NORTH;
    break;
  }
  case(POS_SOUTH_EAST): {
    return POS_NORTH_EAST;
    break;
  }
  case(POS_EAST_SOUTH): {
    return POS_WEST_SOUTH;
    break;
  }
  case(POS_EAST): {
    return POS_WEST;
    break;
  }
  case(POS_EAST_NORTH): {
    return POS_WEST_NORTH;
    break;
  }
  default:
    exit(1);
  }
}

void node_connection(struct node *n1, struct node *n2) {
  if (size_next_nodes(n1) < CONNEXIONS_PER_SIDE && size_next_nodes(n2) < CONNEXIONS_PER_SIDE) {
    n1->next_nodes[size_next_nodes(n1)] = n2;
    n2->next_nodes[size_next_nodes(n2)] = n1;
    ++n1->number_of_nodes;
    ++n2->number_of_nodes;
  } else {
    printf("\nERROR : next_nodes est rempli\n");
    exit(1);
  }
}

void shift_left(struct node *n, int i) {
  for (int j = i; j < CONNEXIONS_PER_SIDE - 1; ++j) {
    n->next_nodes[j] = n->next_nodes[j + 1];
  }
  n->next_nodes[CONNEXIONS_PER_SIDE - 1] = NULL;
}

void node_disconnection(struct node *n1, struct node *n2) {
  for (int i = 0; i < CONNEXIONS_PER_SIDE; ++i) {
    if (n1->next_nodes[i] == n2)
      shift_left(n1, i);
    if (n2->next_nodes[i] == n1)
      shift_left(n2, i);
  }
  --n1->number_of_nodes;
  --n2->number_of_nodes;
}

boolean is_meeple_in_area(struct node *n) {
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
      return TRUE;
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
  return FALSE;
}

void free_node(struct node *n) {
  free(n);
}
 
