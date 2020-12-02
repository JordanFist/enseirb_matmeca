SRC_DIR=src
TST_DIR=tst
BLD_DIR=build

.PHONY:all
all: check
	make -C ${SRC_DIR}

.PHONY: check
check: 
	make -C ${TST_DIR} check

.PHONY: valgrind
valgrind: 
	make -C ${TST_DIR} valgrind

.PHONY: pthreads
pthreads: 
	make -C ${TST_DIR} pthreads

.PHONY: graphs
graphs: 
	python3 graphs.py

.PHONY: clean
clean:
	rm -rf ${BLD_DIR}/*