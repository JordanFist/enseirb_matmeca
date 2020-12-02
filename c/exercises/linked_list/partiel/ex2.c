
/********* DEBUT DU CODE A NE PAS MODIFIER **********************/
#include <stdlib.h>

struct dequeue {
  struct link * l;
};

/* RAPPEL : la dequeue ne peut contenir QUE des entiers positifs ou
   nuls. */

/********** FIN DU CODE A NE PAS MODIFIER ***********************/

/* Mettre en œuvre les fonctions de la dequeue ci-dessous, utilisant
   UNIQUEMENT les fonctions de `struct link` et `struct array`. */

/**
 * Retourne une dequeue vide.
 **/
struct dequeue * dequeue__empty() {
  struct dequeue *dequeue = (struct dequeue *) malloc(sizeof(struct dequeue));
  struct link *link = (struct link *) malloc(sizeof(struct link));
  if (dequeue == NULL || link == NULL)
    exit(1);
  dequeue->link = link;
  *link = lnk__empty();
}

/**
 * Retourne vraie si dequeue est vide sinon faux.
 **/
int dequeue__is_empty(struct dequeue const * dequeue) {
  if (llm__is_end_mark(lnk__first(dequeue->l)) == 1 && llm__is_end_mark(lnk__last(dequeue->l)) ==  1)
    return 1;
  return 0;
}

/**
 * Retourne l'élément en tête de dequeue et -1 en cas d'erreur.
 **/
int dequeue__front(struct dequeue const * dequeue) {
  if (llm__is_end_mark(lnk__first(dequeue->l)) == 0) {
    return *(lnk_first(dequeue->l)->array->first)
  }
  return -1;
}

/**
 * Retourne le nombre d'éléments stockés.
 **/
size_t dequeue__size(struct dequeue const * dequeue) {
  int res = 0;
  struct lelement *e = lnk__first(dequeue->l);
  while (llm__is_end_mark(e) == 0) {
    res += e->array->size;
    e = llm__next(e);
  }
  return res;
}

/**
 * Libère la mémoire allouée pour la dequeue.
 **/
void dequeue__free(struct dequeue * dequeue) {
  struct lelement e = lnk__first(dequeue->l);
  struct lelement e_next = llm__next(e); 
  while (llm__is_end_mark(e) == 0) {
    free(e->array);
    free(e);
    e = e_next;
    e_next = llm__next(e);
  }
  free(dequeue->l);
  free(dequeue);
}

/**
 * Ajoute x en tête de la dequeue,
 * retourne 0 en cas de succès et -1 en cas d'erreur.
 **/
int dequeue__push_front(struct dequeue * dequeue, int x) {
  if (llm__is_end_mark(lnk__first(dequeue->l)) == 0) {
    return (array__push_front(lnk__first(dequeue->l)->array, x)); 
}

