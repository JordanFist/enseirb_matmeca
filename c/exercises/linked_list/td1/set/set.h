#ifndef SET_H
#define SET_H

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE 1

struct set;

struct set *set__empty(void);
int set__is_empty(const struct set *set);
int set__size(const struct set *set);
int set__find(const struct set *set, int element);
int set__add(struct set *set, int element);
int set__remove(struct set *set, int element);
struct set *set__union(struct set *s1, struct set *s2);
struct set *set__filter(struct set *set);
void set__debug_data(struct set *set, char *p);
  
void set__free(struct set *set);

#endif
