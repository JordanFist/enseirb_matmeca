#include <stdio.h>
#include <stdlib.h>
#include <link.h>
#include <set_link.h>
#include <set.h>
#include <assert.h>

#define SENTINEL (lnk__empty().head)

void test__lnk__empty() {
  printf("Test de lnk__empty ");

  struct link l = lnk__empty();
  assert(l.head == SENTINEL); 
  assert(l.tail == SENTINEL);

  printf("\033[31mOK\033[0m\n");
}

void test__lnk__first() {
  printf("Test de lnk__first ");

  struct link l = {SENTINEL, SENTINEL};
  assert(lnk__first(&l) == SENTINEL);

  int a = 2;
  struct lelement e = {&a, SENTINEL};
  struct link l2 = {&e, &e};
  assert(lnk__first(&l2) == &e);

  printf("\033[31mOK\033[0m\n");
}

void test__llm__is_end_mark() {
  printf("Test de llm__is_end_mark ");

  int a = 2;
  struct lelement e = {&a, SENTINEL};
  assert(llm__is_end_mark(&e) == FALSE);
  
  assert(llm__is_end_mark(SENTINEL) == TRUE);

  printf("\033[31mOK\033[0m\n");
}

void test__lnk__add_head() {
  printf("Test de lnk__add_head ");

  struct link l = {SENTINEL, SENTINEL};
  int a = 3;
  struct lelement e = {&a, SENTINEL};
  int res = lnk__add_head(&l, &e);
  assert(l.head == &e);
  assert(l.tail == &e);
  assert(res == SUCCESS);

  int b = 2;
  struct lelement e2 = {&b, SENTINEL};
  lnk__add_head(&l, &e2);
  assert(l.head == &e2);
  assert(e2.next == &e);
  assert(l.tail == &e);

  printf("\033[31mOK\033[0m\n");
}

void test__llm__next() {
  printf("Test de llm__next ");
  
  struct link l = {SENTINEL, SENTINEL};
  assert(llm__next(l.head) == SENTINEL);

  int a = 3, b = 2;;
  struct lelement e = {&a, SENTINEL};
  struct lelement e2 = {&b, &e};
  assert(llm__next(&e2) == &e);

  printf("\033[31mOK\033[0m\n");
}

void test__lnk__remove_head() {
  printf("Test de lnk__remove_head ");

  int a = 3, b = 2;
  struct lelement e = {&a, SENTINEL};
  struct lelement e2 = {&b, &e};
  struct link l = {&e2, &e};
  struct lelement *e3 = lnk__remove_head(&l);
  assert(l.head == &e);
  assert (e3 == &e2);
  assert(l.tail == &e);
  lnk__remove_head(&l);
  assert(l.tail == SENTINEL);

  struct link l2 = {SENTINEL, SENTINEL};
  struct lelement *e4 = lnk__remove_head(&l2);
  assert(l2.head == SENTINEL);
  assert(e4 == SENTINEL);

  printf("\033[31mOK\033[0m\n");
}

void test__lnk__add_after() {
  printf("Test de lnk__add_after ");

  int a = 3, b = 1, c = 2;
  struct lelement e3 = {&a, SENTINEL};
  struct lelement e1 = {&b, &e3};
  struct link l = {&e1, &e3};
  struct lelement e2 = {&c, NULL};
  lnk__add_after(&l, &e1, &e2);
  assert(e2.next == &e3);
  assert(e1.next == &e2);

  int d = 4;
  struct lelement e4 = {&d, NULL};
  int res = lnk__add_after(&l, &e3, &e4);
  assert(res == SUCCESS);
  assert(l.tail == &e4);
  assert(e3.next == &e4);
  
  printf("\033[31mOK\033[0m\n");
}

void test__lnk__remove_after() {
  printf("Test de lnk__remove_after ");

  int a = 3, b = 2, c = 1;
  struct lelement e3 = {&a, SENTINEL};
  struct lelement e2 = {&b, &e3};
  struct lelement e1 = {&c, &e2};
  struct link l = {&e1, &e3};
  struct lelement *remove = lnk__remove_after(&l, &e3);
  assert(remove == SENTINEL);

  remove = lnk__remove_after(&l, &e1);
  assert(remove == &e2);
  assert(e1.next == &e3);
  assert(l.tail == &e3);
  
  remove = lnk__remove_after(&l, &e1);
  assert(remove == &e3);
  assert(l.tail == &e1);
  
  printf("\033[31mOK\033[0m\n");
}

void test__lnk__add_tail() {
  printf("Test de lnk__add_tail ");

  int a = 3, b = 2, c = 1, d = 4;
  struct lelement e3 = {&a, SENTINEL};
  struct lelement e2 = {&b, &e3};
  struct lelement e1 = {&c, &e2};
  struct link l = {&e1, &e3};
  struct lelement e4 = {&d, NULL};
  lnk__add_tail(&l, &e4);
  assert(e3.next == &e4);
  assert(l.tail = &e4);
  assert(e4.next == SENTINEL);

  struct link l2 = {SENTINEL, SENTINEL};
  int e = 5;
  struct lelement e5 = {&e, NULL};
  lnk__add_tail(&l2, &e5);
  assert(l2.tail == &e5);
  assert(l2.head == &e5);
  
  printf("\033[31mOK\033[0m\n");
}

void test__lnk__remove_tail() {
  printf("Test de lnk__remove_tail ");

  int a = 3, b = 2, c = 1;
  struct lelement e3 = {&a, SENTINEL};
  struct lelement e2 = {&b, &e3};
  struct lelement e1 = {&c, &e2};
  struct link l = {&e1, &e3};
  struct lelement *remove = lnk__remove_tail(&l);
  assert(remove == &e3);
  assert(e2.next == SENTINEL);
  assert(l.tail == &e2);

  struct link l2 = {SENTINEL, SENTINEL};
  remove = lnk__remove_tail(&l2);
  assert(remove == SENTINEL);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__empty() {
  printf("Test de set__empty ");
  
  struct set *s1 = set__empty(&compare_int);
  
  assert(set__is_empty(s1) == TRUE);
  assert(s1->l->head == SENTINEL);
  assert(s1->l->tail == SENTINEL);
  set__free(s1);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__is_empty() {
  printf("Test de set__is_empty ");

  struct set *s1 = set__empty(&compare_int);

  assert(set__is_empty(s1) == TRUE);
  assert(s1->l->head == SENTINEL);
  assert(s1->l->tail == SENTINEL);
  set__free(s1);

  struct set *s2 = set__empty(&compare_int);
  int a = 2, b = 1; 
  set__add(s2, &a);
  set__add(s2, &b);

  int *c = (int *)s2->l->head->data;
  int *d = (int *)s2->l->tail->data;
  assert(set__is_empty(s2) == FALSE);
  assert(*c == 1);
  assert(*d == 2);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test__set__size() {
  printf("Test de set__size ");

  struct set *s1 = set__empty(&compare_int);

  assert(set__size(s1) == 0);
  set__free(s1);
  
  struct set *s2 = set__empty(&compare_int);
  int a = 1, b = 2;
  set__add(s2, &a);
  set__add(s2, &b);

  assert(set__size(s2) == 2);
  set__free(s2);
  
  struct set *s3 = set__empty(&compare_int);
  int c = 3;
  set__add(s3, &c);
  set__add(s3, &b);
  set__remove(s3, &b);

  assert(set__size(s3) == 1);
  set__free(s3);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__find() {
  printf("Test de set__find ");
  
  struct set *s1 = set__empty(&compare_int);
  int a = 1, b = 3, c = 2, d = 4;
  set__add(s1, &a);
  set__add(s1, &b);
  set__add(s1, &c);

  assert(set__find(s1, &c) == TRUE);
  assert(set__find(s1, &d) == FALSE);
  set__free(s1);

  struct set *s2 = set__empty(&compare_int);
  set__add(s2, &a);
  set__add(s2, &c);
  set__add(s2, &d);
  set__remove(s2, &d);
  
  assert(set__find(s2, &d) == FALSE);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test__set__add() {
  printf("Test de set__add ");
  
  struct set *s1 = set__empty(&compare_int);
  int a = 2, b = -1;
  set__add(s1, &a);
  int res = set__add(s1, &a);
  int res2 = set__add(s1, &b);

  assert(res2 == FAILURE);
  assert(set__find(s1, &b) == FALSE);
  assert(set__size(s1) == 1);
  int *c = (int *)s1->l->head->data;
  int *d = (int *)s1->l->tail->data;
  assert(*c == 2);
  assert(*d == 2);
  assert(res == FAILURE);
  set__free(s1);
  
  struct set *s2 = set__empty(&compare_int);
  int e = 6, f = 4;
  set__add(s2, &e);
  set__add(s2, &a);
  set__add(s2, &f);
  
  int *g = (int *)s2->l->head->data;
  int *h = (int *)llm__next(s2->l->head)->data;
  int *i = (int *)s2->l->tail->data;
  assert(*g == 2);
  assert(*h == 4);
  assert(*i == 6);
  assert(set__size(s2) == 3);
  set__free(s2);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__remove() {
  printf("Test de set__remove ");

  struct set *s1 = set__empty(&compare_int);
  int a = 2;
  set__remove(s1, &a);

  assert(set__find(s1, &a) == FALSE);
  set__free(s1);

  struct set *s2 = set__empty(&compare_int);
  set__add(s2, &a);
  set__remove(s2, &a);

  assert(set__is_empty(s2) == TRUE);
  set__free(s2);

  struct set *s3 = set__empty(&compare_int);
  int b = 5, c = 7;
  set__add(s3, &b);
  set__add(s3, &c);
  set__add(s3, &a);
  set__remove(s3, &b);

  int *d = (int *)s3->l->head->data;
  int *e = (int *)s3->l->tail->data;
  assert(*d == 2);
  assert(*e == 7);
  assert(set__size(s3) == 2);
  set__free(s3);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__union() {
  printf("Test de set__union ");

  struct set *s1 = set__empty(&compare_int);
  int a = 1, b = 2, c = 3, d = 7;
  set__add(s1, &a);
  set__add(s1, &b);
  set__add(s1, &c);
  set__add(s1, &d);
  struct set *s2 = set__empty(&compare_int);
  int e = 5;
  set__add(s2, &a);
  set__add(s2, &e);
  set__add(s2, &d);
  struct set *s_union = set__union(s1, s2);

  int *f = (int *)s_union->l->head->data;
  int *g = (int *)llm__next(s_union->l->head)->data;
  int *h = (int *)llm__next(llm__next(s_union->l->head))->data;
  int *i = (int *)llm__next(llm__next(llm__next(s_union->l->head)))->data;
  int *j = (int *)s_union->l->tail->data;
  
  assert(*f == 1);
  assert(*g == 2);
  assert(*h == 3);
  assert(*i == 5);
  assert(*j == 7);
  assert(set__size(s_union) == 5);
  set__free(s1);
  set__free(s2);
  set__free(s_union);

  printf("\033[31mOK\033[0m\n");
}

void test__set__filter() {
  printf("Test de set__filter ");

  struct set *s1 = set__empty(&compare_int);
  struct set *s_filter = set__filter(s1, &is_even);

  assert(s_filter->l->head == SENTINEL);
  assert(s_filter->l->tail == SENTINEL);
  set__free(s1);
  set__free(s_filter);

  struct set *s2 = set__empty(&compare_int);
  int a = 4, b = 1, c = 2;
  set__add(s2, &a);
  set__add(s2, &b);
  set__add(s2, &c);
  struct set *s_filter2 = set__filter(s2, &is_even);

  int *d = (int *)s_filter2->l->head->data;
  int *e = (int *)s_filter2->l->tail->data;
  assert(*d == 2);
  assert(*e == 4);
  set__free(s2);
  set__free(s_filter2);
  
  printf("\033[31mOK\033[0m\n");
}

int main() {
  
  test__lnk__empty();
  test__lnk__first();
  test__llm__is_end_mark();
  test__lnk__add_head();
  test__llm__next();
  test__lnk__remove_head();
  test__lnk__add_after();
  test__lnk__remove_after();
  test__lnk__add_tail();
  test__lnk__remove_tail();
  
  test__set__empty();
  test__set__is_empty();
  test__set__size();
  test__set__find();
  test__set__add();
  test__set__remove();
  test__set__union();
  test__set__filter();

  /*
  struct set *s1 = set__empty(compare_int);
  int a = 1, b = 2, c =3, d = 4;
  set__add(s1, &a);
  set__add(s1, &b);
  set__add(s1, &c);
  set__add(s1, &d);
  struct set *s = set__filter(s1, &is_even);
  set__debug_data(s, print);
  */

  return SUCCESS;
}
