#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASH_SIZE 13		// prime number

// Structure d'une cellule : pointeur vers une donnée (fonction, entier, structure, ...) et 2 pointeurs vers une structure cell
struct cell
{
  void *donnee;
  struct cell *next;
  struct cell *prev;
};

// Structure d'une table de hashage : 2 pointeurs de fonction, pointeur vers un pointeur de structure cell (premiere case d'entree) 
struct hash_table
{
  int (*cmp) (void *, void *);
  int (*hash) (void *);
  struct cell **entry;
  int size;
};

// Creer une nouvelle cellule
struct cell *hash_newcell (void *donnee)
{
  struct cell *c = malloc (sizeof (*c));
  c->donnee = donnee;
  c->next = c->prev = NULL;
  return c;
}

// Initialise la table
struct hash_table *hash_init (int (*cmp) (void *, void *),
			      int (*hash) (void *))
{
  struct hash_table *hash_t;
  int i;
  assert (cmp != NULL);
  assert (hash != NULL);
  hash_t = malloc (sizeof (*hash_t));
  if (hash_t == NULL)
    return NULL;
  hash_t->cmp = cmp;
  hash_t->hash = hash;
  hash_t->entry = malloc (sizeof (*(hash_t->entry)) * HASH_SIZE);
  if (hash_t->entry == NULL)
    {
      free (hash_t);
      return NULL;
    }
  hash_t->size = HASH_SIZE;
  for (i = 0; i < hash_t->size; ++i)
    hash_t->entry[i] = NULL;
  return hash_t;
}

// Ajoute une cellule
int hash_add (struct hash_table *hash, void *donnee)
{
  int value;
  int c;
  struct cell *cell = hash_newcell (donnee);
  assert (hash != NULL);
  value = hash->hash (donnee);
  fprintf (stderr, "DEBUG: hash value is %d \n", value);
  if (hash->entry[value % hash->size] == NULL)
    {
      hash->entry[value % hash->size] = cell;
    }
  else
    {
      struct cell *q = NULL, *p = hash->entry[value % hash->size];
      while ((p != NULL) && ((c = hash->cmp (donnee, p->donnee)) > 0))
	{
	  q = p;
	  p = p->next;
	}
      if (c == 0)
	return 1;		// element is already in the table
      if (q == NULL)
	{
	  p->prev = cell;
	  cell->next = p;
	  hash->entry[value % hash->size] = cell;
	}
      else
	{
	  q->next = cell;
	  cell->prev = q;
	}
    }
  return 0;
}

// Cherche une cellule
int hash_cherche (struct hash_table *hash, void *donnee)
{
  int r = 0, value;
  assert (hash != NULL);
  value = hash->hash (donnee);
  struct cell *p = hash->entry[value % hash->size];
  while ((p != NULL) && (r = hash->cmp (donnee, p->donnee) < 0))
    p = p->next;
  if (r == 0)
    return 0;
  if (p == NULL)
    return 1;
  return 1;
}

// Libere une cellule
void hash_free (struct hash_table *hash, void (*release) (void *))
{
  int i;
  assert (hash != NULL);
  for (i = 0; i < hash->size; ++i)
    {
      struct cell *p = hash->entry[i];
      if (p == NULL)
	continue;
      while (p->next != NULL)
	{
	  p = p->next;
	  if (release != NULL)
	    release (p->prev->donnee);
	  free (p->prev);
	}
    }
  free (hash->entry);
  free (hash);
}


