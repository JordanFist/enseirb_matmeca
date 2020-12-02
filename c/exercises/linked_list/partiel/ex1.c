/********* DEBUT DU CODE A NE PAS MODIFIER **********************/
#include <stdlib.h>
#include <stdio.h>

#define CAPACITY 5

struct array {
  int a[CAPACITY];   // tableau d'entier
  int * first;       // pointeur sur 1er élément
  size_t size;       // nombre d'éléments stockés dans a
};

/**
 * Retourne le nombre d'éléments stockés.
 **/
size_t array__size(struct array const * array)
{
  return array->size;
}

/* RAPPEL : un array ne peut contenir QUE des entiers positifs ou
   nuls. */

/********** FIN DU CODE A NE PAS MODIFIER ***********************/

/* Mettre en œuvre les fonctions de array ci-dessous. */

void print(struct array *array) {
  for (int i = 0; i < 5; ++i)
    printf("%d\n", array->a[i]);
  printf("size : %zu \t first : %d \n", array->size, *(array->first));
}

/**
 * Initialise une structure array à vide.
 **/
void array__empty(struct array * array) { 
  array->first = (array->a + CAPACITY/2);
  array->size = 0;
}

/**
 * Ajoute x en tête,
 * retourne 0 en cas de succès et -1 en cas d'erreur.
 **/
int array__push_front(struct array * array, int x) {
  if (array->a < array->first) {
    *(array->first - 1) = x;
    array->first = (array->first - 1);
    ++array->size;
    return 0;
  }
  return -1;
}
  
/**
 * Retourne l'élément en tête ou -1 en cas d'erreur.
 **/
int array__front(struct array const * array) {
  if (array->size != 0)
    return *(array->first);
  return -1;
}


/**
 * Retire l'élement en tête, 
 * retourne 0 en cas de succès et -1 en cas d'erreur.
 **/
int array__pop_front(struct array * array) {
  if (array->size > 0) {
    --array->size;
    array->first = (array->first + 1);
  }
  return -1;
}

/**
 * Ajoute x en queue, 
 * retourne 0 en cas de succès et -1 en cas d'erreur.
 **/
int array__push_back(struct array * array, int x) {
  if ((array->first + array->size) < (array->a + CAPACITY)) {
    *(array->first + array->size) = x;
    ++array->size;
    return 0;
  }
  return -1;
}


/**
 * Retourne l'élément en queue ou -1 en cas d'erreur.
 **/
int array__back(struct array const * array) {
  if (array->size != 0)
    return *(array->first + array->size - 1);
  return -1;
}

/**
 * Retire l'élement en queue, 
 * retourne 0 en cas de succès et -1 en cas d'erreur.
 **/
int array__pop_back(struct array * array) {
  if (array->size > 0)
    --array->size;
  return -1;
}

int main () {
  struct array a = {{-88, -88, -88, -88, -88}, NULL, 6789};
  array__empty(&a);
  array__push_front(&a, 11);
  array__pop_front(&a);
  array__push_front(&a, 12);
  array__push_back(&a, 13);
  //printf("%d\n", array__back(&a));
  array__pop_back(&a);
  printf("%d\n", array__back(&a));
  array__push_back(&a, 15);

  print(&a);
  return 0;
}
