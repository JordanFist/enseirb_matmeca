#include <stdio.h>
#include <stdlib.h>
#include <set_dynamic.h>
#include <set.h>

struct set *set__empty() {
  struct set *set = (struct set *) malloc(sizeof(struct set));
  if (set == NULL)
    exit(1);
  set->s = NULL;
  set->capacity = 0;
  set->size = 0;
  return set;
}

int set__is_empty(const struct set *set) {
  if (set__size(set) == 0)
    return TRUE;
  return FALSE;
}

int set__size(const struct set *set) {
  return set->size;
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
  while (i != len) {
    x = set->s[len - 1];
    set->s[len] = x;
    --len;
  }
}

void shift_left(struct set *set, int i) {
  int len = set__size(set);
  for (int j = i; j < len - 1; ++j) {
    set->s[j] = set->s[j + 1];
  }
  set->s[len - 1] = EMPTY_BOX;
}

void init_set(struct set *set, int i) {
  for (int j = i; j < set->capacity; ++j)
    set->s[j] = EMPTY_BOX;
}

int add_memory(struct set *set) {
  if (set->capacity == 0) 
    set->capacity = 1;
  else
    set->capacity *= 2;
  set->s = (int *) realloc(set->s, set->capacity * sizeof(int));
  if (set->s == NULL)
    exit(1);
  init_set(set, set->capacity/2);
  return SUCCESS;
}

int remove_memory(struct set *set) {
  set->capacity /= 2;
  set->s = (int *) realloc(set->s, set->capacity * sizeof(int));
  if (set->s == NULL && set->capacity != 0)
    exit(1);
  return SUCCESS;
}

int set__add(struct set *set, int element) {
  if (element < 0 || set__find(set, element) == TRUE)
    return FAILURE;
  int len = set__size(set);
  if (len == set->capacity) {
    if (add_memory(set) == FAILURE) 
      return FAILURE;
  }
  for (int i = 0; i < len; ++i) {
    if (element < set->s[i]) {
      shift_right(set, i);
      set->s[i] = element;
      ++set->size;
      return SUCCESS;
    }
  }
  set->s[len] = element;
  ++set->size;
  return SUCCESS;
}

int set__remove(struct set *set, int element) {
  for (int i = 0; i < set__size(set); ++i) {
    if (set->s[i] == element) {
      shift_left(set, i);
      --set->size;
      if (set__size(set) <= set->capacity / 2) 
	remove_memory(set);
      return SUCCESS;
    } 
  }
  return FAILURE;
}

struct set *set__union(struct set *s1, struct set *s2) {
  struct set *s = set__empty();
  int i = 0;
  while (i != set__size(s1) && i != set__size(s2)) {
      set__add(s, s1->s[i]);	
      set__add(s, s2->s[i]);
      ++i;
  }
  if (i == set__size(s1)) {
    while (i != set__size(s2)) {
      set__add(s, s2->s[i]);
      ++i;
    }
  } else {
    while (i != set__size(s1)) {
      set__add(s, s1->s[i]);
      ++i;
    }
  }
  return s;
}

void set__free(struct set *set) {
  free(set->s);
  free(set);
}

struct set *set__filter(struct set *set) {
  struct set *s = set__empty();
  for (int i = 0; i < set__size(set); ++i) {
    if (set->s[i] % 2 == 0)
      set__add(s, set->s[i]);
  }
  return s;
}

void set__debug_data(struct set *set, char *p) {
  for (int i = 0; i < set__size(set); ++i) {
    printf("%d%s", set->s[i], p);
  }
}
