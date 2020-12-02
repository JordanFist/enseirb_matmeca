#ifndef SET_LINK_H
#define SET_LINK_H

#include <link.h>

#define SUPERIOR 1
#define EGAL 0
#define INFERIOR -1

struct set {
  struct link *l;
  int (*mod)(void *, void *);
};

int compare_int(void *int1, void *int2);
int compare_person(void *person1, void *person2);
int is_even(void *element);
int copy(void *element);
void print(void *element);

#endif
