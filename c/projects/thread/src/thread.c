#include <valgrind/valgrind.h>
#include "thread.h"


#define LOCK 1
#define UNLOCK 0

unsigned int last_thread_id = 0;
int priority_min = 0;

TAILQ_HEAD(thread_list, thread) rest, ready, dead;

struct thread_list *head_rest = &rest;
struct thread_list *head_ready = &ready;
struct thread_list *head_dead = &dead;
  
struct thread main_thread;

#define CHECK_MALLOC(p) \
    if ((p) == NULL)    \
    exit(1);


void print_queue(struct thread_list *a) {//utilisé pour debug

    thread_t t1 = TAILQ_FIRST(a);
    thread_t t2 = TAILQ_FIRST(a);
    while (t1 != NULL && t2 != NULL) {
        printf("thread_current: %d, @%p\n", t1->id, t1);
        t2 = t1;
        t1 = TAILQ_NEXT(t1, next);
    }

}

void printd(){
    printf("dead\n");
    print_queue(head_dead);
    printf("ready\n");
    print_queue(head_ready);
    printf("rest\n");
    print_queue(head_rest);
    printf("\n");
}

 #ifdef SCHED_TAIL
 #define INSERT(thread) \
    {(thread)->sorting_order--; \
    struct thread_list * ___dummy = head_ready; \
    if ((thread)->sorting_order < priority_min){ \
        (thread)->sorting_order = (thread)->priority; \
        ___dummy = head_rest; \
    } \
    if (TAILQ_EMPTY(___dummy) || ((TAILQ_FIRST(___dummy))->sorting_order < (thread)->sorting_order)){ \
        TAILQ_INSERT_HEAD(___dummy, (thread), next); \
    }else { \
        thread_t t1 = TAILQ_FIRST(___dummy); \
        while((TAILQ_NEXT(t1, next) != NULL) && ((TAILQ_NEXT(t1,next))->sorting_order > (thread)->sorting_order)){ \
            t1 = TAILQ_NEXT(t1, next);} \
        TAILQ_INSERT_AFTER(___dummy, t1, (thread), next); \
    } \
    if (TAILQ_EMPTY(head_ready)){ \
        ___dummy = head_ready; \
        head_ready = head_rest; \
        head_rest = ___dummy;}} \

#else
#define INSERT(thread) \
     TAILQ_INSERT_TAIL(head_ready, thread, next);
#endif

//================================================================
// Fontions auxiliaires
//================================================================



int incremente_id() {
    return last_thread_id++;
}


int is_dead(thread_t t) {
    return t->is_dead;
}


void init_queue() {
    TAILQ_INIT(head_ready);
    TAILQ_INIT(head_rest);
    TAILQ_INIT(head_dead);
}


void init_context(ucontext_t *uc, int is_main) {
    getcontext(uc);
    uc->uc_stack.ss_size = 64 * 1024;
    if (!(is_main)) {
        uc->uc_stack.ss_sp = malloc(uc->uc_stack.ss_size);
        CHECK_MALLOC(uc->uc_stack.ss_sp);
    }
    uc->uc_link = NULL;
}


void thread_init() {
    ucontext_t *uc_init = &(main_thread.uc);
    main_thread.id = incremente_id();
    main_thread.is_dead = 0;
    main_thread.join_to = NULL;
    main_thread.sorting_order = 0;
    main_thread.priority = 0;
    init_context(uc_init, 1);
    main_thread.valgrind_stackid = VALGRIND_STACK_REGISTER(uc_init->uc_stack.ss_sp,
                                                           uc_init->uc_stack.ss_sp + uc_init->uc_stack.ss_size);
    TAILQ_INSERT_TAIL(head_ready, &main_thread, next);
}


int thread_yield_join(int addattail){
    if (TAILQ_EMPTY(head_ready))
        return EXIT_SUCCESS;
    thread_t first = TAILQ_FIRST(head_ready);
    TAILQ_REMOVE(head_ready, TAILQ_FIRST(head_ready), next);
    if (addattail) {
        INSERT(first);
    } else if (TAILQ_EMPTY(head_ready) && !TAILQ_EMPTY(head_rest)){
        struct thread_list * ___dummy = head_ready; 
        head_ready = head_rest; 
        head_rest = ___dummy;
    }
    thread_t second = TAILQ_FIRST(head_ready);
    return swapcontext(&(first->uc), &(second->uc));
}
 

int only_main_left() {
    if (!TAILQ_EMPTY(head_rest)){
        return 0;}    
    TAILQ_REMOVE(head_ready, TAILQ_FIRST(head_ready), next);
    int emptyness = TAILQ_EMPTY(head_ready);
    TAILQ_INSERT_HEAD(head_ready, (thread_t) &main_thread, next);
    return emptyness;
}


void thread_routine(void *(*func)(void *), void *funcarg) {
    thread_exit(func(funcarg));
}


//================================================================
// Fontions principales
//================================================================


thread_t thread_self(void) {
    if (TAILQ_FIRST(head_ready) == NULL) { //Vérifie si le malloc fonctionne
        init_queue();
        thread_init();
    }
    return TAILQ_FIRST(head_ready);
}


int thread_create(thread_t *newthread, void *(*func)(void *), void *funcarg) {
    if (TAILQ_EMPTY(head_ready)) {
        init_queue();
        thread_init();
    }
    *newthread = malloc(sizeof(**newthread));
    CHECK_MALLOC(*newthread);
    ucontext_t *uc = &((*newthread)->uc);
    init_context(uc, 0);
    (*newthread)->id = incremente_id();
    (*newthread)->is_dead = 0;
    (*newthread)->priority = 0;
    (*newthread)->sorting_order = 0;
    (*newthread)->join_to = NULL;
    (*newthread)->valgrind_stackid = VALGRIND_STACK_REGISTER(uc->uc_stack.ss_sp,
                                                             uc->uc_stack.ss_sp + uc->uc_stack.ss_size);
    makecontext(uc, (void (*)(void))thread_routine, 2, func, funcarg);
    INSERT(*newthread);
    thread_yield();
    return EXIT_SUCCESS;
}


int thread_yield(void) {
    return thread_yield_join(1);
}


void thread_exit(void *retval) {
    thread_t t = TAILQ_FIRST(head_ready);
    thread_t join = t->join_to;

    if (t == &main_thread){//if you try to thread_exit main with others threads running
        t->retval = retval;
        t->is_dead = 1;
        if(join != NULL)
            INSERT(join);//wakes the thread which want to join 

        while(!only_main_left())
            thread_yield();

        while(!TAILQ_EMPTY(head_dead)) {
            t = TAILQ_FIRST(head_dead);
            TAILQ_REMOVE(head_dead, t, next);
            VALGRIND_STACK_DEREGISTER(t->valgrind_stackid);
            free(t->uc.uc_stack.ss_sp);
            free(t);
        }
        exit(0);
    }
    TAILQ_REMOVE(head_ready, TAILQ_FIRST(head_ready), next);
    t->retval = retval;
    t->is_dead = 1;
    TAILQ_INSERT_TAIL(head_dead, t, next);

    if (join != NULL){
        INSERT(join);
    } else if (TAILQ_EMPTY(head_ready) && !TAILQ_EMPTY(head_rest)){
        struct thread_list * ___dummy = head_ready; 
        head_ready = head_rest; 
        head_rest = ___dummy;
    }

    if (!(setcontext(&(TAILQ_FIRST(head_ready)->uc))))
        exit(1);
    exit(0); //Jamais atteint, permet de faire taire le compilateur
}


int thread_join(thread_t thread, void **retval) {
    if (thread == NULL)
        return -1;
    
    if (!(is_dead(thread))) {

        thread->join_to = TAILQ_FIRST(head_ready);
        thread_yield_join(0);
    }
    if (retval != NULL)
        *retval = thread->retval;
    if (thread != &main_thread) {
        TAILQ_REMOVE(head_dead, thread, next);
        VALGRIND_STACK_DEREGISTER(thread->valgrind_stackid);
        free(thread->uc.uc_stack.ss_sp);
        free(thread);
    }
    return EXIT_SUCCESS;
}


int thread_mutex_init(thread_mutex_t *mutex)
{
    mutex->dummy = UNLOCK;
    mutex->waiting = malloc(sizeof(struct thread_waiting));
    CHECK_MALLOC(mutex->waiting);
    TAILQ_INIT(mutex->waiting);
    return EXIT_SUCCESS;
}

int thread_mutex_destroy(thread_mutex_t *mutex)
{  
    assert(TAILQ_EMPTY(mutex->waiting));
    free(mutex->waiting);
    return EXIT_SUCCESS;
}

int thread_mutex_lock(thread_mutex_t *mutex)
{
    if (mutex != NULL)
    { 
        if (mutex->dummy){
            thread_t first = thread_self();
            mutex_thread_t t = malloc(sizeof(struct mutex_thread));
            t->thread = first;
            TAILQ_INSERT_TAIL(mutex->waiting, t, next);
            thread_yield_join(0);
        }
        mutex->dummy = LOCK;                        
    }
    return EXIT_SUCCESS;
}

int thread_mutex_unlock(thread_mutex_t *mutex)
{
    if (mutex != NULL){
        if (mutex->dummy){
            mutex->dummy = UNLOCK;
            if (!TAILQ_EMPTY(mutex->waiting)){                
                mutex_thread_t t = TAILQ_FIRST(mutex->waiting);
                thread_t th = t->thread;
                TAILQ_REMOVE(mutex->waiting, t, next);
                free(t);
                mutex->dummy = LOCK;
                INSERT(th);
            }
    }}
    return EXIT_SUCCESS;
}


int thread_set_priority(thread_t thread, int priority) {
    thread->priority = priority;
    thread->sorting_order = priority;
    if (priority_min > priority)
        priority_min = priority;
    return EXIT_SUCCESS;
}