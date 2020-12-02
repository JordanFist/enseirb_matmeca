#ifndef SET_DYNAMIC_H
#define SET_DYNAMIC_H

struct set {
  struct node **n;
  int capacity;
  int size;
};

struct set *set__empty(void);
int set__is_empty(const struct set *set);
int set__size(const struct set *set);
int set__find(const struct set *set, struct node *n);
int set__add(struct set *set, struct node *n);
struct node *set__remove(struct set *set);
void set__free(struct set *set);

void init_set(struct set *set, int i);
int add_memory(struct set *set);
int remove_memory(struct set *set);
void shift_right_dynamic(struct set *set, int i);

#endif
