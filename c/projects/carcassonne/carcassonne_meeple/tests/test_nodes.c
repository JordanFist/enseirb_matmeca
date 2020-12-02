#include <stdio.h>
#include <stdlib.h>
#include <nodes.h>
#include <assert.h>
#include <set_dynamic.h>
#include <set_graph.h>
#include <graph.h>

/*POUR L'AFFICHAGE*/
char FAIL[]="\033[31;1mFAIL\033[0m";
char PASSED[]="\033[32;1mPASSED\033[0m";

void test_init_node() {
  printf("Test de init_node .............");
  
  struct node *n = init_node(0, 0);

  assert(n->land_type == PLAIN);
  assert(n->meeple == FALSE);
  assert(n->meeple_owner == NO_PLAYER);
  assert(n->number_of_nodes == 0);
  for (int i = 0; i < CONNEXIONS_PER_SIDE; ++i)
    assert(n->next_nodes[i] == NULL);

  free_node(n);
  printf("%s\n",PASSED);
}

void test_landscape_node() {
  printf("Test de landscape_node  .............");
  
  struct node *n = init_node(1, 0);
  assert(landscape_node(n) == PLAIN);

  struct node *n2 = init_node(23, 1);
  assert(landscape_node(n2) == ROAD);

  free_node(n);
  free_node(n2);
  printf("%s\n",PASSED);
}

void test_size_next_node() {
  printf("Test de size_next_node .............");
  
  struct node *n1 = init_node(0, 0);
  struct node *n2 = init_node(0, 0);

  assert(size_next_nodes(n1) == 0);
  assert(size_next_nodes(n2) == 0);
  
  node_connection(n1, n2);

  assert(size_next_nodes(n1) == 1);
  assert(size_next_nodes(n2) == 1);
  
  free_node(n1);
  free_node(n2);
  printf("%s\n",PASSED);
}

void test_oppossite_node() {
  printf("Test de oppossite_node .............");
  
  int res = opposite_node(8);
  assert(res == 0);

  res = opposite_node(1);
  assert(res == 7);
  
  printf("%s\n",PASSED);
}

void test_node_connection() {
  printf("Test de node_connection .............");

  struct node *n1 = init_node(0, 0);
  struct node *n2 = init_node(0, 0);
  
  node_connection(n1, n2);

  assert(n1->next_nodes[0] == n2);
  assert(n2->next_nodes[0] == n1);
  assert(n1->next_nodes[1] == NULL);
  assert(n2->next_nodes[1] == NULL);

  free_node(n1);
  free_node(n2);
  
  printf("%s\n",PASSED);
}

void test_node_disconnection() {
  printf("Test de node_disconnection .............");

  struct node *n1 = init_node(0, 0);
  struct node *n2 = init_node(0, 1);
  struct node *n3 = init_node(0, 2);
  
  node_connection(n1, n2);
  node_connection(n2, n3);
  node_disconnection(n1, n2);

  for (int i = 0; i < CONNEXIONS_PER_SIDE; ++i)
    assert(n1->next_nodes[i] == NULL);

  assert(n2->next_nodes[0] == n3);
  assert(n3->next_nodes[0] == n2);
  assert(n2->next_nodes[1] == NULL);
  assert(n3->next_nodes[1] == NULL);
  assert(n1->number_of_nodes == 0);
  assert(n2->number_of_nodes == 1);
  assert(n3->number_of_nodes == 1);

  free_node(n1);
  free_node(n2);
  free_node(n3);

  printf("%s\n",PASSED);
}

void test_shift_left() {
  printf("Test de shift_left .............");

  struct node *n1 = init_node(0, 0);
  struct node *n2 = init_node(0, 0);
  struct node *n3 = init_node(0, 0);
  node_connection(n1, n2);
  node_connection(n2, n3);
  
  shift_left(n1, 0);
  shift_left(n2, 1);

  assert(n1->next_nodes[0] == NULL);
  assert(n1->next_nodes[0] == NULL);
  assert(n2->next_nodes[1] == NULL);
  assert(n2->next_nodes[0] != NULL);
  assert(n3->next_nodes[0] != NULL);

  free_node(n1);
  free_node(n2);
  free_node(n3);
  
  printf("%s\n",PASSED);
}

void test_is_meeple_in_area() {
  printf("Test de is_meeple_in_area .............");

  struct node *n1 = init_node(1, 1);
  struct node *n2 = init_node(1, 2);
  struct node *n3 = init_node(1, 3);
  struct node *n4 = init_node(1, 4);
  struct node *n5 = init_node(1, 5);
  struct node *n6 = init_node(1, 6);

  node_connection(n1, n2);
  node_connection(n2, n3);
  node_connection(n3, n4);
  node_connection(n4, n5);
  node_connection(n3, n6);

  n5->meeple = TRUE;

  int res = is_meeple_in_area(n6);
  assert(res == TRUE);

  free_node(n1);
  free_node(n2);
  free_node(n3);
  free_node(n4);
  free_node(n5);
  free_node(n6);

  
  struct move m1 = {0, 0, 16, {0, 0}, 0, 0};
  struct move m2 = {0, 0, 9, {0, 1}, 3, 1};
  /*
  struct move m3 = {0, 0, 1, {0, -1}, 0, 1};
  struct move m4 = {0, 0, 11, {-1, 0}, 0, 1};
  struct move m5 = {0, 0, 16, {1, 0}, 2, 7};
  struct move m6 = {0, 0, 9, {0, 2}, 0, 1};
  struct move m7 = {0, 0, 1, {0, -2}, 1, 1};
  struct move m8 = {0, 0, 2, {1, 0}, 0, 12};
  */
  //struct move m9 = {0, 0, 19, {-1, -1}, 2, 13};
  //struct move m10 = {0, 0, 0, {-1, 1}, 1, 13};
  //struct move m11 = {0, 0, 8, {0, -2}, 1, 13};
  
  struct graph *g = init_graph();

  add_tail_tile (g, &m1);
  add_tail_tile (g, &m2);
  add_meeple_in_graph(g, &m2);

  assert(g->tiles[0]->nodes[0]->next_nodes[2] == g->tiles[1]->nodes[8]);

  res = is_meeple_in_area(g->tiles[0]->nodes[0]);
  assert(res == FALSE);

  /*
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 13; ++j) {
      printf("%p\n", g->tiles[i]->nodes[j]);
      //for (int k = 0; k < 4; ++k) {
      //printf("%p\n", g->tiles[i]->nodes[j]->next_nodes[k]);
      //}
    }
printf("\n");
}*/
  /*
  add_tail_tile (g, &m3);
  add_tail_tile (g, &m4);
  add_tail_tile (g, &m5);
  add_tail_tile (g, &m6);
  add_tail_tile (g, &m7);
  add_tail_tile (g, &m8);
  */
  //add_tail_tile (g, &m9);
  //add_tail_tile (g, &m10);
  //add_tail_tile (g, &m11);
  



  
  printf("%s\n",PASSED);
}

int main() {
  test_init_node();
  test_landscape_node();
  test_size_next_node();
  test_oppossite_node();
  test_node_connection();
  test_node_disconnection();
  test_shift_left();
  test_is_meeple_in_area();
  
  return EXIT_SUCCESS;
}
