#ifndef HASH_H
#define HASH_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cell *hash_newxell (void *donnee);
struct hash_table *hash_init (int (*cmp) (void *, void *), int (*hash) (void *));
int hash_add (struct hash_table *hash, void *donnee);
int hash_cherche (struct hash_table *hash, void *donnee);
void hash_free (struct hash_table *hash, void (*release) (void *));
int str_hash (unsigned char *str);

#endif
