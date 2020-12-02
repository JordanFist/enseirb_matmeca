#include <stdio.h>
#include <assert.h>
#include <set.h>
#if defined SENTINEL
#include <set_sentinel.h>
#elif defined DYNAMIC
#include <set_dynamic.h>
#elif defined LINK
#include <set_link.h>
#else
#error "A set implementation has to be defined"
#endif

void test__set__is_empty() {
  printf("Test de set__is_empty ");
  
  //set__is_empty : emsemble vide
  struct set *s1 = set__empty(&compare_int);
  assert (set__is_empty(s1) == TRUE);
  set__free(s1);

  //set__is_empty: ensemble  non  vide
  struct  set *s2 = set__empty(&compare_int);
  int a = 1;
  int b = 17;
  set__add (s2, &a);
  set__add (s2, &b);
  assert(set__is_empty(s2) == FALSE);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test__set__size() {
  printf("Test de set__size ");
  
  struct set *s1 = set__empty(&compare_int);
  assert(set__size(s1) == 0);
  set__free(s1);

  struct set *s2 = set__empty(&compare_int);
  int a = 3, b = 4;
  set__add(s2, &a);
  if (set__find(s2, &a) == TRUE)
    assert(set__size(s2) == 1);
  if (set__find(s2, &b) == FALSE)
    assert(set__size(s2) == 1);
  set__free(s2);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__find() {
  printf("Test de set__find ");
  
  struct set *s1 = set__empty(&compare_int);
  int a = 3;
  assert(set__find(s1, &a) == FALSE);
  set__free(s1);

  struct set *s2 = set__empty(&compare_int);
  int b = 4;
  set__add(s2, &b);
  assert(set__find(s2, &b) == TRUE);
  set__free(s2);

  struct set *s3 = set__empty(&compare_int);
  struct set *s4 = set__empty(&compare_int);
  int c = 1, d = 2;
  set__add(s3, &c);
  set__add(s4, &c);
  set__add(s4, &d);
  assert(set__find(s3, &c) == TRUE);
  assert(set__find(s4, &c) == TRUE);
  set__free(s3);
  set__free(s4);

  printf("\033[31mOK\033[0m\n"); 
}

void test__set__add() {
  printf("Test de set__add ");
  
  struct set *s1 = set__empty(&compare_int);
  int a = 5, b = 15;
  set__add(s1, &a);
  set__add(s1, &b);
  assert(set__find(s1, &a) == TRUE);
  assert(set__find(s1, &b) == TRUE);
  set__free(s1);
  
  struct set *s2 = set__empty(&compare_int);
  int c = -2;
  int res = set__add(s2, &c);
  assert(res == FAILURE);
  assert(set__find(s2, &c) == FALSE);
  set__free(s2);

  struct set *s3 = set__empty(&compare_int);
  int d = 2;
  set__add(s3, &d);
  res = set__add(s3, &d);
  assert(res == FAILURE);
  set__free(s3);

  printf("\033[31mOK\033[0m\n"); 
}

void test__set__remove() {
  printf("Test de set__remove ");
  
  struct set *s1 = set__empty(&compare_int);
  int a = 5;
  set__remove(s1, &a);
  assert(set__is_empty(s1) == TRUE);
  set__free(s1);

  struct set *s2 = set__empty(&compare_int);
  set__add(s2, &a);
  set__remove(s2, &a);
  assert(set__is_empty(s2) == TRUE);
  set__free(s2);

  struct set *s3 = set__empty(&compare_int);
  struct set *s4 = set__empty(&compare_int);
  int b = 4;
  set__add(s3, &a);
  set__add(s3, &b);
  set__remove(s3, &a);
  set__add(s4, &a);
  set__remove(s4, &a);
  set__add(s4, &b);
  assert(set__find(s3, &b) == TRUE);
  assert(set__find(s4, &b) == TRUE);
  assert(set__find(s3, &a) == FALSE);
  assert(set__find(s4, &a) == FALSE);
  assert(set__size(s3) == set__size(s4));
  set__free(s3);
  set__free(s4);
  
  printf("\033[31mOK\033[0m\n"); 
}

void test__set__union() {
  printf("Test de set__union ");
  
  struct set *s1 = set__empty(&compare_int);
  struct set *s2 = set__empty(&compare_int);
  int a = 3, b = 1;
  set__add(s2, &a);
  set__add(s2, &b);
  struct set *s_union = set__union(s1, s2);
  
  assert(set__size(s_union) == 2);
  assert(set__find(s_union, &b) == TRUE);
  assert(set__find(s_union, &a) == TRUE);
  set__free(s1);
  set__free(s2);
  set__free(s_union);

  struct set *s3 = set__empty(&compare_int);
  int c = 2;
  set__add(s3, &c);
  struct set *s4 = set__empty(&compare_int);
  set__add(s4, &a);
  struct set *s5 = set__empty(&compare_int);
  set__add(s5, &c);
  set__add(s5, &b);
  struct set *s6 = set__empty(&compare_int);
  set__add(s6, &a);
  
  struct set *s_union2 = set__union(s3, s4);
  set__add(s_union2, &b);
  struct set *s_union3 = set__union(s5, s6);

  assert(set__find(s_union2, &b) == TRUE);
  assert(set__find(s_union3, &b) == TRUE);
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

  struct set *s1 = set__empty(&compare_int);
  struct set *s_filter = set__filter(s1, &is_even);

  assert(set__is_empty(s_filter) == TRUE);
  set__free(s1);
  set__free(s_filter);

  struct set *s2 = set__empty(&compare_int);
  int a = 2, b = 10, c = 5, d = 12, e = 1, f = 6;
  set__add(s2, &a);
  set__add(s2, &b);
  set__add(s2, &c);
  set__add(s2, &d);
  set__add(s2, &e);
  set__add(s2, &f);
  struct set *s_filter2 = set__filter(s2, &is_even);

  assert(set__find(s_filter2, &a) == TRUE);
  assert(set__find(s_filter2, &b) == TRUE);
  assert(set__find(s_filter2, &d) == TRUE);
  assert(set__find(s_filter2, &f) == TRUE);
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
