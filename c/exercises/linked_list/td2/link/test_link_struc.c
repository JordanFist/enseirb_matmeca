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

  struct lelement e = {2, SENTINEL};
  struct link l2 = {&e, &e};
  assert(lnk__first(&l2) == &e);

  printf("\033[31mOK\033[0m\n");
}

void test__llm__is_end_mark() {
  printf("Test de llm__is_end_mark ");

  struct lelement e = {2, SENTINEL};
  assert(llm__is_end_mark(&e) == FALSE);
  
  assert(llm__is_end_mark(SENTINEL) == TRUE);

  printf("\033[31mOK\033[0m\n");
}

void test__lnk__add_head() {
  printf("Test de lnk__add_head ");

  struct link l = {SENTINEL, SENTINEL};
  struct lelement e = {3, SENTINEL};
  int res = lnk__add_head(&l, &e);
  assert(l.head == &e);
  assert(l.tail == &e);
  assert(res == SUCCESS);
  
  struct lelement e2 = {2, SENTINEL};
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

  struct lelement e = {3, SENTINEL};
  struct lelement e2 = {2, &e};
  assert(llm__next(&e2) == &e);

  printf("\033[31mOK\033[0m\n");
}

void test__lnk__remove_head() {
  printf("Test de lnk__remove_head ");
  
  struct lelement e = {3, SENTINEL};
  struct lelement e2 = {2, &e};
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

  struct lelement e3 = {3, SENTINEL};
  struct lelement e1 = {1, &e3};
  struct link l = {&e1, &e3};
  struct lelement e2 = {2, NULL};
  lnk__add_after(&l, &e1, &e2);
  assert(e2.next == &e3);
  assert(e1.next == &e2);

  struct lelement e4 = {4, NULL};
  int res = lnk__add_after(&l, &e3, &e4);
  assert(res == SUCCESS);
  assert(l.tail == &e4);
  assert(e3.next == &e4);
  
  printf("\033[31mOK\033[0m\n");
}

void test__lnk__remove_after() {
  printf("Test de lnk__remove_after ");

  struct lelement e3 = {3, SENTINEL};
  struct lelement e2 = {2, &e3};
  struct lelement e1 = {1, &e2};
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

  struct lelement e3 = {3, SENTINEL};
  struct lelement e2 = {2, &e3};
  struct lelement e1 = {1, &e2};
  struct link l = {&e1, &e3};
  struct lelement e4 = {4, NULL};
  lnk__add_tail(&l, &e4);
  assert(e3.next == &e4);
  assert(l.tail = &e4);
  assert(e4.next == SENTINEL);

  struct link l2 = {SENTINEL, SENTINEL};
  struct lelement e5 = {5, NULL};
  lnk__add_tail(&l2, &e5);
  assert(l2.tail == &e5);
  assert(l2.head == &e5);
  
  printf("\033[31mOK\033[0m\n");
}

void test__lnk__remove_tail() {
  printf("Test de lnk__remove_tail ");

  struct lelement e3 = {3, SENTINEL};
  struct lelement e2 = {2, &e3};
  struct lelement e1 = {1, &e2};
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
  
  struct set *s1 = set__empty();
  
  assert(set__is_empty(s1) == TRUE);
  assert(s1->l->head == SENTINEL);
  assert(s1->l->tail == SENTINEL);
  set__free(s1);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__is_empty() {
  printf("Test de set__is_empty ");

  struct set *s1 = set__empty();

  assert(set__is_empty(s1) == TRUE);
  assert(s1->l->head == SENTINEL);
  assert(s1->l->tail == SENTINEL);
  set__free(s1);

  struct set *s2 = set__empty();
  set__add(s2, 2);
  set__add(s2, 1);

  assert(set__is_empty(s2) == FALSE);
  assert(s2->l->head->data == 1);
  assert(s2->l->tail->data == 2);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test__set__size() {
  printf("Test de set__size ");

  struct set *s1 = set__empty();

  assert(set__size(s1) == 0);
  set__free(s1);
  
  struct set *s2 = set__empty();
  set__add(s2, 1);
  set__add(s2, 2);

  assert(set__size(s2) == 2);
  set__free(s2);
  
  struct set *s3 = set__empty();
  set__add(s3, 3);
  set__add(s3, 2);
  set__remove(s3, 2);

  assert(set__size(s3) == 1);
  set__free(s3);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__find() {
  printf("Test de set__find ");
  
  struct set *s1 = set__empty();
  set__add(s1, 1);
  set__add(s1, 3);
  set__add(s1, 2);

  assert(set__find(s1, 2) == TRUE);
  assert(set__find(s1, 4) == FALSE);
  set__free(s1);

  struct set *s2 = set__empty();
  set__add(s2, 1);
  set__add(s2, 2);
  set__add(s2, 4);
  set__remove(s2, 4);
  
  assert(set__find(s2, 4) == FALSE);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test__set__add() {
  printf("Test de set__add ");
  
  struct set *s1 = set__empty();
  set__add(s1, 2);
  int res = set__add(s1, 2);
  int res2 = set__add(s1, -1);

  assert(res2 == FAILURE);
  assert(set__find(s1, -1) == FALSE);
  assert(set__size(s1) == 1);
  assert(s1->l->head->data == 2);
  assert(s1->l->tail->data == 2);
  assert(res == FAILURE);
  set__free(s1);

  struct set *s2 = set__empty();
  set__add(s2, 6);
  set__add(s2, 2);
  set__add(s2, 4);

  assert(s2->l->head->data == 2);
  assert(llm__next(s2->l->head)->data == 4);
  assert(s2->l->tail->data == 6);
  assert(set__size(s2) == 3);
  set__free(s2);

  printf("\033[31mOK\033[0m\n");
}

void test__set__remove() {
  printf("Test de set__remove ");

  struct set *s1 = set__empty();
  set__remove(s1, 2);

  assert(set__find(s1, 2) == FALSE);
  set__free(s1);

  struct set *s2 = set__empty();
  set__add(s2, 2);
  set__remove(s2, 2);

  assert(set__is_empty(s2) == TRUE);
  set__free(s2);

  struct set *s3 = set__empty();
  set__add(s3, 5);
  set__add(s3, 7);
  set__add(s3, 2);
  set__remove(s3, 5);

  assert(s3->l->head->data == 2);
  assert(s3->l->tail->data == 7);
  assert(set__size(s3) == 2);
  set__free(s3);
  
  printf("\033[31mOK\033[0m\n");
}

void test__set__union() {
  printf("Test de set__union ");

  struct set *s1 = set__empty();
  set__add(s1, 1);
  set__add(s1, 2);
  set__add(s1, 3);
  set__add(s1, 7);
  struct set *s2 = set__empty();
  set__add(s2, 1);
  set__add(s2, 5);
  set__add(s2, 7);
  struct set *s_union = set__union(s1, s2);

  assert(s_union->l->head->data == 1);
  assert(llm__next(s_union->l->head)->data == 2);
  assert(llm__next(llm__next(s_union->l->head))->data == 3);
  assert(llm__next(llm__next(llm__next(s_union->l->head)))->data == 5);
  assert(s_union->l->tail->data == 7);
  assert(set__size(s_union) == 5);
  set__free(s1);
  set__free(s2);
  set__free(s_union);

  printf("\033[31mOK\033[0m\n");
}

int pair(int n) {
  if (n % 2 == 0)
    return TRUE;
  return FALSE;
}

int copy(int n) {
  if (n > 0)
    return TRUE;
  return TRUE;
}

void test__set__filter() {
  printf("Test de set__filter ");

  struct set *s1 = set__empty();
  struct set *s_filter = set__filter(s1, &pair);

  assert(s_filter->l->head == SENTINEL);
  assert(s_filter->l->tail == SENTINEL);
  set__free(s1);
  set__free(s_filter);

  struct set *s2 = set__empty();
  set__add(s2, 4);
  set__add(s2, 1);
  set__add(s2, 2);
  struct set *s_filter2 = set__filter(s2, &pair);

  assert(s_filter2->l->head->data == 2);
  assert(s_filter2->l->tail->data == 4);
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
  struct set *s1 = set__empty();
  set__add(s1, 1);
  set__add(s1, 2);
  set__add(s1, 3);
  set__add(s1, 4);
  struct set *s = set__filter(s1, &pair);
  set__debug_data(s, "\n");
  */

  return SUCCESS;
}
