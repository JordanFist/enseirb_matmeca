#include <stdio.h>
#include <stdlib.h>
#include <link.h>

static const struct lelement sentinel = {INT_MAX, (struct lelement *) &sentinel};
// static => on le voit que dans ce fichier
// ne pas mettre sentinel dans le .h 
#define SENTINEL ((struct lelement *) &sentinel)

struct link lnk__empty() {
  struct link link = {SENTINEL, SENTINEL};
  return link;
}

struct lelement *lnk__first(const struct link *l) {
  return l->head;
}

int llm__is_end_mark(const struct lelement *e) {
  return (e == SENTINEL);
}

int lnk__add_head(struct link *l, struct lelement *e) {
  if (llm__is_end_mark(lnk__first(l)) == TRUE)
    l->tail = e;
  e->next = l->head;
  l->head = e;
  return (l->head == e && e->next == l->head);
}

struct lelement *llm__next(const struct lelement *e) {
  return (e->next);
}

struct lelement *lnk__remove_head(struct link *l) {
  struct lelement *remove = l->head; 
  if (l->head != SENTINEL) {
    l->head = llm__next(l->head);
    remove->next = NULL;
    if (llm__is_end_mark(lnk__first(l)) == TRUE)
      l->tail = SENTINEL;
  }
  return remove;
}

int lnk__add_after(struct link *l, struct lelement *e, struct lelement *e_add) {
  if (e != SENTINEL) {
    if (llm__is_end_mark(llm__next(e)) == TRUE) 
      l->tail = e_add;
    e_add->next = e->next;
    e->next = e_add;
  }
  return (e->next == e_add && e_add->next == e->next);
}
  
struct lelement *lnk__remove_after(struct link *l, struct lelement *e) {
  struct lelement *remove = SENTINEL;
  if (llm__is_end_mark(llm__next(e)) == FALSE) {
    if (llm__is_end_mark(llm__next(llm__next(e))) == TRUE)
      l->tail = e;
    remove = e->next;
    e->next = llm__next(llm__next(e));
    remove->next = NULL;
  }
  return remove;
}
  
int lnk__add_tail(struct link *l, struct lelement *e_add) {
  if (l->tail == SENTINEL)
    return lnk__add_head(l, e_add);
  return lnk__add_after(l, l->tail, e_add);
}

struct lelement *lnk__remove_tail(struct link *l) {
  struct lelement *e = l->head;
  while (llm__is_end_mark(llm__next(llm__next(e))) == FALSE) {
    e = llm__next(e);
  }
  return (lnk__remove_after(l, e));
}

