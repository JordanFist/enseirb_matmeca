#include <set_sentinel.h>
#include <set.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_set__empty() {
  printf("test de set__empty ");
  
  struct set *s1 = set__empty();
  
  for (int i = 0; i < SET__SIZE; ++i)
    assert(s1->s[i] == SENTINEL);
  set__free(s1);

  printf("\033[31mOK\033[0m\n");
}

void test__set__is_empty() {
  printf("test de set__is_empty ");
  
  struct set *s1 = set__empty();
  
  assert(s1->s[0] == SENTINEL);
  assert(set__is_empty(s1) == TRUE);
  set__free(s1);
  
  struct set *s2 = set__empty();
  set__add(s2, 1);
  set__add(s2, 2);
  
  assert(s2->s[0] != SENTINEL);
  assert(set__is_empty(s2) == FALSE);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test__set__size() {
  printf("test de set__size ");

  struct set *s1 = set__empty();
  set__add(s1, 1);
  set__add(s1, 2);
  set__add(s1, 3);
  
  assert(set__size(s1) == 3);
  set__free(s1);
  
  struct set *s2 = set__empty();
  set__add(s2, 1);
  set__add(s2, 2);
  set__remove(s2, 1);
  
  assert(set__size(s2) == 1);
  set__free(s2);
  
  struct set *s3 = set__empty();
  
  assert(set__size(s3) == 0);
  set__free(s3);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__find() {
  printf("test de set__find ");
  
  struct set *s1 = set__empty();
  set__add(s1, 1);
  set__add(s1, 3);
  set__add(s1, 2);
  
  assert(set__find(s1, 1) == TRUE);
  assert(s1->s[0] == 1);
  assert(set__find(s1, 4) == FALSE);
  set__free(s1);
  
  struct set *s2 = set__empty();
  set__add(s2, 7);
  set__add(s2, 2);
  set__remove(s2, 2);
  
  assert(set__find(s2, 2) == FALSE);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test__set__add() {
  printf("test de set__add ");

  struct set *s1 = set__empty();
  set__add(s1, 1);
  int res = set__add(s1, 1);
  int res2 = set__add(s1, -1);

  assert(res2 == FAILURE);
  assert(set__find(s1, -1) == FALSE);
  assert(s1->s[0] == 1);
  assert(res == FAILURE);
  assert(s1->s[1] == SENTINEL);

  set__free(s1);

  struct set *s2 = set__empty();
  set__add(s2, 5);
  set__add(s2, 1);
  set__add(s2, 3);
  
  assert(s2->s[0] == 1);
  assert(s2->s[1] == 3);
  assert(s2->s[2] == 5);
  assert(s2->s[3] == SENTINEL);
  set__free(s2);
  
  struct set *s3 = set__empty();
  for (int i = 0; i < SET__SIZE - 1; ++i)
    s3->s[i] = i;
  set__add(s3, 10);
  
  assert(set__find(s3, 10) == FALSE);
  set__free(s3);

  printf("\033[31mOK\033[0m\n");
}

void test__set__remove() {
  printf("test de set__remove ");
  
  struct set *s1 = set__empty();
  set__add(s1, 1);
  set__add(s1, 2);
  set__add(s1, 3);
  set__remove(s1, 2);
  
  assert(s1->s[0] == 1);
  assert(s1->s[1] == 3);
  assert(s1->s[2] == SENTINEL);
  assert(set__find(s1, 2) == FALSE);
  set__free(s1);
  
  struct set *s2 = set__empty();
  set__remove(s2, 10);
  
  assert(set__is_empty(s2) == TRUE);
  set__free(s2);

  struct set *s3 = set__empty();
  set__add(s3, 1);
  set__remove(s3, 1);
  
  assert(set__is_empty(s3) == TRUE);
  set__free(s3);
    
  printf("\033[31mOK\033[0m\n");
}

int pair(int n) {
  if (n % 2 == 0)
    return TRUE;
  return FALSE;
}

void test__set__filter() {
  printf("test de set__filter ");

  struct set *s1 = set__empty();
  struct set *s_filter = set__filter(s1, &pair);

  assert(s_filter->s[0] == SENTINEL);
  set__free(s1);
  set__free(s_filter);

  struct set *s2 = set__empty();
  set__add(s2, 2);
  set__add(s2, 1);
  set__add(s2, 4);
  struct set *s_filter2 = set__filter(s2, &pair);

  assert(s_filter2->s[0] == 2);
  assert(s_filter2->s[1] == 4);
  assert(set__size(s_filter2) == 2);
  set__free(s2);
  set__free(s_filter2);
  
  printf("\033[31mOK\033[0m\n");
}

void test_shift_right() {
  printf("test de shift_right ");
  
  struct set *s1 = set__empty();
  set__add(s1, 1);
  shift_right(s1, 0);
  
  assert(set__size(s1) == 2);
  assert(s1->s[0] == EMPTY_BOX);
  assert(s1->s[1] == 1);
  assert(s1->s[2] == SENTINEL);
  set__free(s1);
  
  struct set *s2 = set__empty();
  set__add(s2, 1);
  set__add(s2, 2);
  set__add(s2, 3);
  set__add(s2, 4);
  shift_right(s2, 2);
  
  assert(set__size(s2) == 5);
  assert(s2->s[2] == EMPTY_BOX);
  assert(s2->s[3] == 3);
  assert(s2->s[4] == 4);
  assert(s2->s[5] == SENTINEL);
  set__free(s2);

  struct set *s3 = set__empty();
  shift_right(s3, 0);
  
  assert(s3->s[0] == EMPTY_BOX);
  assert(s3->s[1] == SENTINEL);
  set__free(s3);
  
  printf("\033[31mOK\033[0m\n");
}

void test_shift_left() {
  printf("test de shift_left ");

  struct set *s1 = set__empty();
  set__add(s1, 1);
  shift_left(s1, 0);
  
  assert(set__is_empty(s1) == TRUE);
  set__free(s1);

  struct set *s2 = set__empty();
  set__add(s2, 1);
  set__add(s2, 2);
  set__add(s2, 3);
  set__add(s2, 4);
  shift_left(s2, 1);
  assert(set__size(s2) == 3);
  assert(s2->s[0] == 1);
  assert(s2->s[1] == 3);
  assert(s2->s[2] == 4);
  assert(s2->s[3] == SENTINEL);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test_set__union() {
  printf("test de set__union ");

  struct set *s1 = set__empty();
  struct set *s2 = set__empty();
  struct set *s_union = set__union(s1, s2);
  
  assert(set__is_empty(s_union) == TRUE);
  set__free(s1);
  set__free(s2);
  set__free(s_union);

  struct set *s3 = set__empty();
  set__add(s3, 1);
  set__add(s3, 2);
  set__add(s3, 3);
  struct set *s4 = set__empty();
  set__add(s4, 1);
  set__add(s4, 3);
  set__add(s4, 6);
  struct set *s_union2 = set__union(s3, s4);

  assert(set__size(s_union2) == 4);
  assert(s_union2->s[0] == 1);
  assert(s_union2->s[1] == 2);
  assert(s_union2->s[2] == 3);
  assert(s_union2->s[3] == 6);
  assert(s_union2->s[4] == SENTINEL);
  set__free(s3);
  set__free(s4);
  set__free(s_union2);

  printf("\033[31mOK\033[0m\n");
}

int main() {
  test_set__empty();
  test__set__is_empty();
  test__set__size();
  test__set__find();
  test__set__add();
  test__set__remove();
  test_set__union();
  test__set__filter();
  
  test_shift_right();
  test_shift_left();
 
  return SUCCESS;
}
