#ifndef __THREAD_H__
#define __THREAD_H__

#ifndef USE_PTHREAD
#define _XOPEN_SOURCE 600

#include <sys/queue.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>
#include <assert.h>

/* identifiant de thread
 * NB: pourra être un entier au lieu d'un pointeur si ca vous arrange,
 *     mais attention aux inconvénient des tableaux de threads
 *     (consommation mémoire, cout d'allocation, ...).
 */
  
typedef struct thread { 
    int id;
    void * retval;
    int valgrind_stackid;
    int is_dead;
    int sorting_order;
    int priority;
    ucontext_t uc;
    TAILQ_ENTRY(thread) next;
    struct thread* join_to;
} * thread_t;


typedef struct mutex_thread {
    thread_t thread;
    TAILQ_ENTRY(mutex_thread) next;
} * mutex_thread_t;


/* recuperer l'identifiant du thread courant.
 */
extern thread_t thread_self(void);

/* creer un nouveau thread qui va exécuter la fonction func avec l'argument funcarg.
 * renvoie 0 en cas de succès, -1 en cas d'erreur.
 */
extern int thread_create(thread_t *newthread, void *(*func)(void *), void *funcarg);

/* passer la main à un autre thread.
 */
extern int thread_yield(void);

/* attendre la fin d'exécution d'un thread.
 * la valeur renvoyée par le thread est placée dans *retval.
 * si retval est NULL, la valeur de retour est ignorée.
 */
extern int thread_join(thread_t thread, void **retval);

/* terminer le thread courant en renvoyant la valeur de retour retval.
 * cette fonction ne retourne jamais.
 *
 * L'attribut noreturn aide le compilateur à optimiser le code de
 * l'application (élimination de code mort). Attention à ne pas mettre
 * cet attribut dans votre interface tant que votre thread_exit()
 * n'est pas correctement implémenté (il ne doit jamais retourner).
 */
extern void thread_exit(void *retval) __attribute__ ((__noreturn__));

/* change la priorité du thread passé en paramêtre 
 * pour la priorité passée en paramètre
 * si aucun flag n'est défini, la priorité n'est pas prise en compte
 */
extern int thread_set_priority(thread_t thread, int priority);

/* Interface possible pour les mutex */
TAILQ_HEAD(thread_waiting, mutex_thread);
typedef struct thread_mutex { int dummy; struct thread_waiting *waiting;} thread_mutex_t;
int thread_mutex_init(thread_mutex_t *mutex);
int thread_mutex_destroy(thread_mutex_t *mutex);
int thread_mutex_lock(thread_mutex_t *mutex);
int thread_mutex_unlock(thread_mutex_t *mutex);

#else /* USE_PTHREAD */

/* Si on compile avec -DUSE_PTHREAD, ce sont les pthreads qui sont utilisés */
#include <sched.h>
#include <pthread.h>
#define thread_t pthread_t
#define thread_self pthread_self
#define thread_create(th, func, arg) pthread_create(th, NULL, func, arg)
#define thread_yield sched_yield
#define thread_join pthread_join
#define thread_exit pthread_exit

/* Interface possible pour les mutex */
#define thread_mutex_t            pthread_mutex_t
#define thread_mutex_init(_mutex) pthread_mutex_init(_mutex, NULL)
#define thread_mutex_destroy      pthread_mutex_destroy
#define thread_mutex_lock         pthread_mutex_lock
#define thread_mutex_unlock       pthread_mutex_unlock

#endif /* USE_PTHREAD */

#endif /* __THREAD_H__ */
