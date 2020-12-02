#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include "thread.h"

/* test des priotites
 *
 * le programme doit retourner correctement.
 * valgrind doit être content.
 *
 * support nécessaire:
 * - thread_create()
 * - thread_exit()
 * - thread_join() avec récupération valeur de retour
 * - thread_set_priority()
 * - être compillé avec -DSCHED_TAIL
 */

volatile int nb_nloop = 100000;

static void * thfunc(void *mycpt) {
    unsigned long * mydt = (unsigned long *)mycpt;
    thread_yield();
    thread_yield();
    while (nb_nloop>0) {
        mydt[0]++;
        nb_nloop--;
        thread_yield();
    }
    thread_exit((void*)0xdeadbeef);
    return NULL; /* unreachable, shut up the compiler */
}



int main(int argc, char* argv[]) {

    if (argc < 3) {
        printf("argument manquant: priorites\n");
        return -1;
    }

    int prio1 = atoi(argv[1]);
    int prio2 = atoi(argv[2]);

    thread_t th, th2;

    int err;
    void *res = NULL;
    unsigned long cpt1[1] = {0};
    unsigned long cpt2[1] = {0};

    err = thread_create(&th, thfunc, (void*) cpt1);
    assert(!err);
    thread_set_priority(th, prio1);

    err = thread_create(&th2, thfunc, (void*) cpt2);
    assert(!err);
    thread_set_priority(th2, prio2);


    err = thread_join(th, &res);
    assert(!err);
    assert(res == (void*) 0xdeadbeef);

    err = thread_join(th2, &res);
    assert(!err);
    assert(res == (void*) 0xdeadbeef);

    printf("Scores: thread 1: %ld   thread 2: %ld\n", cpt1[0], cpt2[0]);
    return 0;
}
