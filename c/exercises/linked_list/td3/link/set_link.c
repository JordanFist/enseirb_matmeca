#include <stdio.h>
#include <stdlib.h>
#include <set_link.h>
#include <link.h>
#include <set.h>

int compare_int(void *int1, void *int2) {
  int *n1 = (int *)int1;
  int *n2 = (int *)int2;
  if (int2 == NULL) {
    int zero = 0;
    n2 = &zero; 
  }
  if ((*n1) < (*n2))
    return INFERIOR;
  else if ((*n1) == (*n2))
    return EGAL;
  else
    return SUPERIOR;
}

int compare_person(void *person1, void *person2) {
  struct person *p1 = (struct person *)person1;
  struct person *p2 = (struct person *)person2;
  if (person2 == NULL)
    p2 = NULL;
  if (p1->firstname == p2->firstname && p1->lastname == p2->lastname && p1->year == p2->year && p1->month == p2->month && p1->day == p2->day)
    return EGAL;
  else 
    return SUPERIOR; 
}

struct set *set__empty(int (*mod)(void *, void *)) {
  struct link *l = (struct link *) malloc(sizeof(struct link));
  if (l == NULL)
    exit(1);
  *l = lnk__empty();
  struct set *set = (struct set *) malloc(sizeof(struct set));
  if (set == NULL)
    exit(1);
  set->l = l;
  set->mod = mod;
  return set;
}

int set__is_empty(const struct set *set) {
  return (llm__is_end_mark(lnk__first(set->l)) == TRUE);
}

int set__size(const struct set *set) {
  struct lelement *e = lnk__first(set->l);
  int size = 0;
  while (llm__is_end_mark(e) == FALSE) {
    ++size;
    e = llm__next(e);
  }
  return size;
}

int set__find(const struct set *set, void *element) {
  struct lelement *e = lnk__first(set->l);
  while (llm__is_end_mark(e) == FALSE) {
    if (set->mod(e->data, element) == EGAL)
      return TRUE;
    e = llm__next(e);
  }
  return FALSE;
}

int set__add(struct set *set, void *element) {
  int *null = NULL;
  if (set->mod(element, null) == INFERIOR || set__find(set, element) == TRUE)
    return FAILURE;
  struct lelement *e = lnk__first(set->l);
  struct lelement *e_add = (struct lelement *) malloc(sizeof(struct lelement));
  if (e_add == NULL)
    exit(1);
  e_add->data = element;
  if (set->mod(element, e->data) == INFERIOR)
    return lnk__add_head(set->l, e_add);
  while (llm__is_end_mark(e) == FALSE) {
    if (set->mod(element, llm__next(e)->data) == INFERIOR)
      return lnk__add_after(set->l, e, e_add);
    e = llm__next(e);
  }
  return FAILURE;
}

int set__remove(struct set *set, void *element) {
  struct lelement *e = lnk__first(set->l);
  if (set->mod(element, e->data) == EGAL) {
    struct lelement *remove = lnk__remove_head(set->l);
    free(remove);
    return SUCCESS;
  }
  while (llm__is_end_mark(e) == FALSE) {
    if (set->mod(llm__next(e)->data, element) == EGAL) {
      struct lelement *remove2 = lnk__remove_after(set->l, e);
      free(remove2);
      return SUCCESS;
    }
    e = llm__next(e);
  }
  return FAILURE;
}

void set__free(struct set *set) {
  struct lelement *e = lnk__first(set->l);
  struct lelement *e_free = lnk__first(set->l);
  while (llm__is_end_mark(e) == FALSE) {
    e = llm__next(e);
    free(e_free);
    e_free = e;
  }
  free(set->l);
  free(set);
}

struct set *set__union(struct set *s1, struct set *s2) { 
  struct set *s = set__empty(s1->mod);
  struct lelement *e1 = s1->l->head;
  struct lelement *e2 = s2->l->head;
  while(llm__is_end_mark(e1) == FALSE && llm__is_end_mark(e2) == FALSE) {
    set__add(s, e1->data);
    set__add(s, e2->data);
    e1 = llm__next(e1);
    e2 = llm__next(e2);
  }
  if (llm__is_end_mark(e1) == TRUE) {
    while (llm__is_end_mark(e2) == FALSE) {
      set__add(s, e2->data);
      e2 = llm__next(e2);
    }
  } else {
    while (llm__is_end_mark(e1) == FALSE) {
      set__add(s, e1->data);
      e1 = llm__next(e1);
    }
  }
  return s;
}

int is_even(void *element) {
  int *e = (int *)element;
  if ((*e) % 2 == 0)
    return TRUE;
  return FALSE;
}

int copy(void *element) {
  int *e = (int *)element;
  if (*e > 0)
    return TRUE;
  return TRUE;
}

struct set *set__filter(struct set *set, int (*filter)(void *)) {
  struct set *s = set__empty(set->mod);
  struct lelement *e = lnk__first(set->l);
  while(llm__is_end_mark(e) == FALSE) {
    if (filter(e->data) == TRUE)
      set__add(s, e->data);
    e = llm__next(e);
  }
  return s;
}

void set__debug_data(struct set *set, void (*print)(void *)) {
  struct lelement *e = lnk__first(set->l);
  while (llm__is_end_mark(e) == FALSE) {
    print(e->data);
    e = llm__next(e);
  }
}

void print(void *element) {
  int *e = (int *)element;
  printf("%d\n", *e);
}


