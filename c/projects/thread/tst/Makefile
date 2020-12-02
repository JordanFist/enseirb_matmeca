#================================================================
# Make check
#================================================================
SRC_DIR=../src
BLD_DIR=../build

CHECK_SRC=${wildcard *.c}
CHECK_OBJ=${CHECK_SRC:.c=}
CHECK_FLAGS=-Wall -Wextra -g -O3 -Wno-deprecated-declarations -I ${SRC_DIR}
THREADS_TOINCLUDE= ${BLD_DIR}/thread.o


.PHONY: all
all: check

.PHONY: check
check: check_thread.o ${CHECK_OBJ} check_run check_prios_test check_prios_fibo check_run_prios

check_thread.o: ${SRC_DIR}/thread.c
	${CC} ${CHECK_FLAGS} -c $^ -o ${BLD_DIR}/thread.o


check_prios_test: ${SRC_DIR}/thread.c 71-priorities.c
	${CC} ${CHECK_FLAGS} -DSCHED_TAIL $^ -o ${BLD_DIR}/71-priorities-TAIL

check_prios_fibo: ${SRC_DIR}/thread.c 51-fibonacci.c
	${CC} ${CHECK_FLAGS} -DSCHED_TAIL $^ -o ${BLD_DIR}/51-fibonacci-TAIL

%: %.c
	${CC} ${CHECK_FLAGS} $^ ${THREADS_TOINCLUDE} -o ${BLD_DIR}/$@

check_run:
	./${BLD_DIR}/01-main
	./${BLD_DIR}/02-switch
	./${BLD_DIR}/21-create-many 10
	./${BLD_DIR}/23-create-many-once 10
	./${BLD_DIR}/11-join
	./${BLD_DIR}/12-join-main
	./${BLD_DIR}/22-create-many-recursive 10
	./${BLD_DIR}/31-switch-many 10 10
	./${BLD_DIR}/32-switch-many-join 10 10
	./${BLD_DIR}/51-fibonacci 20
	./${BLD_DIR}/61-mutex 10
	./${BLD_DIR}/71-priorities 1 1

check_run_prios: 
	./${BLD_DIR}/51-fibonacci-TAIL 20
	./${BLD_DIR}/71-priorities-TAIL 10 1


#================================================================
# Make pthreads
#================================================================
.PHONY: pthreads
pthreads: THREADS_TOINCLUDE = ${BLD_DIR}/thread.o -DUSE_PTHREAD -lpthread
pthreads: check_thread.o ${CHECK_OBJ} check_run

#================================================================
# Make valgrind
#================================================================
.PHONY: valgrind
valgrind: check_thread.o ${CHECK_OBJ} valgrind_run

valgrind_run:
	valgrind ./${BLD_DIR}/01-main
	valgrind ./${BLD_DIR}/02-switch
	valgrind ./${BLD_DIR}/21-create-many 10
	valgrind ./${BLD_DIR}/23-create-many-once 10
	valgrind ./${BLD_DIR}/11-join
	valgrind ./${BLD_DIR}/12-join-main
	valgrind ./${BLD_DIR}/22-create-many-recursive 10
	valgrind ./${BLD_DIR}/31-switch-many 10 10
	valgrind ./${BLD_DIR}/32-switch-many-join 10 10
	valgrind ./${BLD_DIR}/51-fibonacci 20
	valgrind ./${BLD_DIR}/61-mutex 10
	valgrind ./${BLD_DIR}/71-priorities 10 1
