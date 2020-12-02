#include <stdio.h>
#include <stdlib.h>
#include <set_link.h>
#include <link.h>
#include <set.h>

struct set *set__empty() {
  struct link *l = malloc(sizeof(struct link));
  *l = lnk__empty();
  struct set *set = malloc(sizeof(struct set));
  set->l = l;
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

int set__find(const struct set *set, int element) {
  struct lelement *e = lnk__first(set->l);
  while (llm__is_end_mark(e) == FALSE) {
    if (e->data == element)
      return TRUE;
    e = llm__next(e);
  }
  return FALSE;
}

int set__add(struct set *set, int element) {
  if (element < 0 || set__find(set, element) == TRUE)
    return FAILURE;
  struct lelement *e = lnk__first(set->l);
  struct lelement *e_add = malloc(sizeof(struct lelement));
  if (e_add == NULL)
    return FAILURE;
  e_add->data = element;
  if (element < e->data) 
    return lnk__add_head(set->l, e_add);
  while (llm__is_end_mark(e) == FALSE) {
    if (element < llm__next(e)->data) 
      return lnk__add_after(set->l, e, e_add);
    e = llm__next(e);
  }
  return FAILURE;
}

int set__remove(struct set *set, int element) {
  struct lelement *e = lnk__first(set->l);
  if (element == e->data) {
    struct lelement *remove = lnk__remove_head(set->l);
    free(remove);
    return SUCCESS;
  }
  while (llm__is_end_mark(e) == FALSE) {
    if (llm__next(e)->data == element) {
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
  struct set *s = set__empty();
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

struct set *set__filter(struct set *set, int (*filter)(int)) {
  struct set *s = set__empty();
  struct lelement *e = lnk__first(set->l);
  while(llm__is_end_mark(e) == FALSE) {
    if (filter(e->data) == TRUE)
      set__add(s, e->data);
    e = llm__next(e);
  }
  return s;
}

void set__debug_data(struct set *set, char *p) {
  struct lelement *e = lnk__first(set->l);
  while (llm__is_end_mark(e) == FALSE) {
    printf("%d%s", e->data, p);
    e = llm__next(e);
  }
}
