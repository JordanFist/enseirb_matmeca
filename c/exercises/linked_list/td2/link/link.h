#ifndef LINK_H
#define LINK_H

#include <limits.h>
#include <set.h>

struct lelement {
  int data;
  struct lelement *next;
};

struct link {
  struct lelement *head;
  struct lelement *tail;
};

struct link lnk__empty();
struct lelement *lnk__first(const struct link *l);
int llm__is_end_mark(const struct lelement *e);
int lnk__add_head(struct link *l, struct lelement *e);
struct lelement *llm__next(const struct lelement *e);
struct lelement *lnk__remove_head(struct link *l);
int lnk__add_after(struct link *l, struct lelement *e, struct lelement *e_add);
struct lelement *lnk__remove_after(struct link *l, struct lelement *e);
int lnk__add_tail(struct link *l, struct lelement *e_add);
struct lelement *lnk__remove_tail(struct link *l);

#endif
