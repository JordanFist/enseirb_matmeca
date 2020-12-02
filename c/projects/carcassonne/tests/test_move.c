#include <moves.h>
#include <assert.h>
#include <stdio.h>
#include <assert.h>
#include <server.h>
#include <stdlib.h>

char FAIL[]="\033[31;1mFAIL\033[0m";
char PASSED[]="\033[32;1mPASSED\033[0m";

struct move m1 = {0, 0, 0, {0, 0}, 0, 0};
struct move m2 = {1, 1, 1, {1, 1}, 1, 1};
struct move m3 = {0, 2, 2, {2, 2}, 0, 2};
struct move m4 = {1, 3, 3, {3, 3}, 0, 3};
struct move m5 = {0, 4, 4, {4, 4}, 0, 4};

void test_init_moves() {
  printf("Test de init_moves ......... ");

  struct moves *m = init_moves();
  assert(m->count_moves == 0);
  
  free_moves(m);
  printf("%s\n", PASSED);
}

void test_add_move() {
  printf("Test de add_move ......... ");
  
  struct moves *m = init_moves();
  add_move(m, &m1);
  add_move(m, &m2);
  assert(m->move_player[0].card == m1.card);
  assert(m->move_player[1].card == m2.card);
  assert(m->count_moves == 2);

  free_moves(m);
  printf("%s\n", PASSED);
}

void test_last_n_moves() {
  printf("Test de last_n_moves ......... ");
  
  struct moves *m = init_moves();
  add_move(m, &m1);
  add_move(m, &m2);
  add_move(m, &m3);
  add_move(m, &m4);

  struct move *m_last = last_n_moves(m, 2);
  assert(m_last[0].card == m3.card);
  assert(m_last[1].card == m4.card);

  struct move *m_last2 = last_n_moves(m, 3);
  assert(m_last2[0].card == m2.card);
  assert(m_last2[1].card == m3.card);
  assert(m_last2[2].card == m4.card);

  free_moves(m);
  printf("%s\n", PASSED);
}

int main (){
  test_init_moves();
  test_add_move();
  test_last_n_moves();
  
  return 0;
}
