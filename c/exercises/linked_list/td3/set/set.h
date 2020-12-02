#ifndef SET_H
#define SET_H

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE 1

struct set;

struct person {
  char *firstname;
  char *lastname;
  unsigned int year;
  unsigned char month;
  unsigned char day;
};

struct set *set__empty(int (*mod)(void *, void *));
int set__is_empty(const struct set *set);
int set__size(const struct set *set);
int set__find(const struct set *set, void *element);
int set__add(struct set *set, void *element);
int set__remove(struct set *set, void *element);
struct set *set__union(struct set *s1, struct set *s2);
struct set *set__filter(struct set *set, int (*filter)(void *));
void set__debug_data(struct set *set, void (*print)(void *));
int is_even(void *element);
  
void set__free(struct set *set);

#endif
