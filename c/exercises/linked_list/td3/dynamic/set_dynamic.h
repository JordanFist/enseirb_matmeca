#ifndef SET_SENTINEL_H
#define SET_SENTINEL_H

#define EMPTY_BOX -2

struct set {
  int *s;
  int capacity;
  int size;
};

void shift_right(struct set* set, int i);
void shift_left(struct set* set, int i);
void init_set(struct set *set, int i);
int add_memory(struct set *set);
int remove_memory(struct set *set);

#endif
