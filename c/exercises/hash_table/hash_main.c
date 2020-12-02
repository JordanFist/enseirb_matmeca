#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

int str_hash (unsigned char *str)
{
  int hash = 5381;
  int c;

  while ((c = *str++) != '\0')
    hash = ((hash << 5) + hash) + c;

  return hash;
}

int main ()
{
  struct hash_table *hash = hash_init ((void *) strcmp, (void *) str_hash);
  printf ("add toto %d \n", hash_add (hash, "toto"));
  printf ("add titi %d \n", hash_add (hash, "titi"));
  printf ("ajout titi %d \n", hash_add (hash, "titi"));
  printf ("toto => %d\n", hash_cherche (hash, "toto"));
  printf ("titi => %d\n", hash_cherche (hash, "titi"));
  printf ("tbtb => %d\n", hash_cherche (hash, "tbtb"));
  hash_free (hash, NULL);
  return EXIT_SUCCESS;
}
