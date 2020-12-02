#ifndef SET_SENTINEL_H
#define SET_SENTINEL_H

#define SET__SIZE 10
#define SENTINEL -1
#define EMPTY_BOX -2

struct set {
  int s[SET__SIZE];
};

void shift_right(struct set* set, int i);
void shift_left(struct set* set, int i);

#endif
