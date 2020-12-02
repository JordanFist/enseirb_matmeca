#include <stdio.h>
#include <stdlib.h>
#include <set_sentinel.h>
#include <set.h>

struct set *set__empty() {
  struct set *set = (struct set *) malloc(sizeof(struct set));
  if (set == NULL)
    exit(1);
  for (int i = 0; i < SET__SIZE; ++i)
    set->s[i] = SENTINEL;
  return set;
}

int set__is_empty(const struct set *set) {
  if (set->s[0] == SENTINEL)
    return TRUE;
  return FALSE;
}

int set__size(const struct set *set) {
  int i = 0;
  while (set->s[i] != SENTINEL)
    ++i;
  return i;
}

int set__find(const struct set *set, int element) {
  int a = 0;
  int b = set__size(set);
  int moy = (a + b) / 2;
  while (a < b) {
    if (set->s[moy] == element)
      return TRUE;
    if (set->s[moy] > element)
      b = moy;
    else
      a = moy + 1;
    moy = (a + b) / 2;
  }
  return FALSE;
}

void shift_right(struct set *set, int i) {
  int len = set__size(set);
  int x;
  while (i != len + 1) {
    x = set->s[len];
    set->s[len + 1] = x;
    --len;
  }
  set->s[len + 1] = EMPTY_BOX;
}

void shift_left(struct set *set, int i) {
  while (set->s[i] != SENTINEL) {
    set->s[i] = set->s[i + 1];
    ++i;
  }
}

int set__add(struct set *set, int element) {
  if (element < 0 || set__find(set, element) == TRUE)
    return FAILURE;
  int i = 0;
  if (set__size(set) + 1 < SET__SIZE) {
    while (set->s[i] != SENTINEL) {
      if (element < set->s[i]) {
	shift_right(set, i);
	set->s[i] = element;
	return SUCCESS;
      }
      ++i;
    }
    shift_right(set, i);
    set->s[i] = element;
    return SUCCESS;
  }
  return FAILURE;
}

int set__remove(struct set *set, int element) {
  int i = 0;
  while (set->s[i] != SENTINEL) {
    if (set->s[i] == element) {
      shift_left(set, i);
      return SUCCESS;
    }
    ++i;
  }
  return FAILURE;
}

struct set *set__union(struct set *s1, struct set *s2) {
  struct set *s = set__empty();
  if (set__size(s1) + set__size(s2) + 1 < SET__SIZE) {
    int i = 0;
    while (s1->s[i] != SENTINEL && s2->s[i] != SENTINEL) {
	set__add(s, s1->s[i]);	
	set__add(s, s2->s[i]);
	++i;
    }
    if (s1->s[i] == SENTINEL) {
      while (s2->s[i] != SENTINEL) {
	set__add(s, s2->s[i]);
	++i;
      }
    } else {
      while (s1->s[i] != SENTINEL) {
	set__add(s, s1->s[i]);
	++i;
      }
    }
  }
  return s;
}

void set__free(struct set *set) {
  free(set);
}

struct set *set__filter(struct set *set) {
  struct set *s = set__empty();
  int i = 0;
  while (set->s[i] != SENTINEL) {
    if (set->s[i] % 2 == 0)
      set__add(s, set->s[i]);
    ++i;
  }
  return s;
}

void set__debug_data(struct set *set, char *p) {
  int i = 0;
  while (set->s[i] != SENTINEL) {
    printf("%d%s", set->s[i], p);
    ++i;
  }
}

