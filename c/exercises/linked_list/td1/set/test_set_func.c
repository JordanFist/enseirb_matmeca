#include <stdio.h>
#include <assert.h>
#include <set.h>
#if defined SENTINEL
#include <set_sentinel.h>
#elif defined DYNAMIC
#include <set_dynamic.h>
#elif defined LINK
#include <set_link.h>
#endif

void test__set__is_empty() {
  printf("Test de set__is_empty ");
  
  //set__is_empty : emsemble vide
  struct set *s1 = set__empty();
  assert (set__is_empty(s1) == TRUE);
  set__free(s1);

  //set__is_empty: ensemble  non  vide
  struct  set *s2 = set__empty();
  set__add (s2, 1);
  set__add (s2, 17);
  assert(set__is_empty (s2) == FALSE);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test__set__size() {
  printf("Test de set__size ");
  
  struct set *s1 = set__empty();
  assert(set__size(s1) == 0);
  set__free(s1);

  struct set *s2 = set__empty();
  set__add(s2, 3);
  if (set__find(s2, 3) == TRUE)
    assert(set__size(s2) == 1);
  if (set__find(s2, 4) == FALSE)
    assert(set__size(s2) == 1);
  set__free(s2);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__find() {
  printf("Test de set__find ");
  
  struct set *s1 = set__empty();
  assert(set__find(s1, 3) == FALSE);
  set__free(s1);

  struct set *s2 = set__empty();
  set__add(s2, 4);
  assert(set__find(s2, 4) == TRUE);
  set__free(s2);

  struct set *s3 = set__empty();
  struct set *s4 = set__empty();
  set__add(s3, 1);
  set__add(s4, 1);
  set__add(s4, 2);
  assert(set__find(s3, 1) == TRUE);
  assert(set__find(s4, 1) == TRUE);
  set__free(s3);
  set__free(s4);

  printf("\033[31mOK\033[0m\n"); 
}

void test__set__add() {
  printf("Test de set__add ");
  
  struct set *s1 = set__empty();
  set__add(s1, 5);
  set__add(s1, 15);
  assert(set__find(s1, 5) == TRUE);
  assert(set__find(s1, 15) == TRUE);
  set__free(s1);
  
  struct set *s2 = set__empty();
  int res = set__add(s2, -2);
  assert(res == FAILURE);
  assert(set__find(s2, -2) == FALSE);
  set__free(s2);

  struct set *s3 = set__empty();
  set__add(s3, 2);
  res = set__add(s3, 2);
  assert(res == FAILURE);
  set__free(s3);

  printf("\033[31mOK\033[0m\n"); 
}

void test__set__remove() {
  printf("Test de set__remove ");
  
  struct set *s1 = set__empty();
  set__remove(s1, 5);
  assert(set__is_empty(s1) == TRUE);
  set__free(s1);

  struct set *s2 = set__empty();
  set__add(s2, 5);
  set__remove(s2, 5);
  assert(set__is_empty(s2) == TRUE);
  set__free(s2);

  struct set *s3 = set__empty();
  struct set *s4 = set__empty();
  set__add(s3, 5);
  set__add(s3, 4);
  set__remove(s3, 5);
  set__add(s4, 5);
  set__remove(s4, 5);
  set__add(s4, 4);
  assert(set__find(s3, 4) == TRUE);
  assert(set__find(s4, 4) == TRUE);
  assert(set__find(s3, 5) == FALSE);
  assert(set__find(s4, 5) == FALSE);
  assert(set__size(s3) == set__size(s4));
  set__free(s3);
  set__free(s4);
  
  printf("\033[31mOK\033[0m\n"); 
}

void test__set__union() {
  printf("Test de set__union ");
  
  struct set *s1 = set__empty();
  struct set *s2 = set__empty();
  set__add(s2, 3);
  set__add(s2, 1);
  struct set *s_union = set__union(s1, s2);
  
  assert(set__size(s_union) == 2);
  assert(set__find(s_union, 1) == TRUE);
  assert(set__find(s_union, 3) == TRUE);
  set__free(s1);
  set__free(s2);
  set__free(s_union);

  struct set *s3 = set__empty();
  set__add(s3, 2);
  struct set *s4 = set__empty();
  set__add(s4, 3);
  struct set *s5 = set__empty();
  set__add(s5, 2);
  set__add(s5, 1);
  struct set *s6 = set__empty();
  set__add(s6, 3);
  
  struct set *s_union2 = set__union(s3, s4);
  set__add(s_union2, 1);
  struct set *s_union3 = set__union(s5, s6);

  assert(set__find(s_union2, 1) == TRUE);
  assert(set__find(s_union3, 1) == TRUE);
  assert(set__size(s_union2) == set__size(s_union3));
  set__free(s3);
  set__free(s4);
  set__free(s5);
  set__free(s6);
  set__free(s_union2);
  set__free(s_union3);
  
  printf("\033[31mOK\033[0m\n"); 
}

void test__set__filter() {
  printf("Test de set__filter ");

  struct set *s1 = set__empty();
  struct set *s_filter = set__filter(s1);

  assert(set__is_empty(s_filter) == TRUE);
  set__free(s1);
  set__free(s_filter);

  struct set *s2 = set__empty();
  set__add(s2, 2);
  set__add(s2, 10);
  set__add(s2, 5);
  set__add(s2, 12);
  set__add(s2, 1);
  set__add(s2, 6);
  struct set *s_filter2 = set__filter(s2);

  assert(set__find(s_filter2, 2) == TRUE);
  assert(set__find(s_filter2, 6) == TRUE);
  assert(set__find(s_filter2, 10) == TRUE);
  assert(set__find(s_filter2, 12) == TRUE);
  assert(set__size(s_filter2) == 4);
  set__free(s2);
  set__free(s_filter2);
  
  printf("\033[31mOK\033[0m\n"); 
}

int main() {
  test__set__is_empty();
  test__set__size();
  test__set__find();
  test__set__add();
  test__set__remove();
  test__set__union();
  test__set__filter();
  
  return SUCCESS;
}
