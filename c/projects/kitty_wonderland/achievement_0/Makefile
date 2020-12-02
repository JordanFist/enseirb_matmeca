EXECUTABLE=main

.PHONY: all
all: $(EXECUTABLE) 

$(EXECUTABLE):
	make -C src
	@cp src/$(EXECUTABLE) .
	./$(EXECUTABLE)

.PHONY: test
test:
	make -C tests

.PHONY: clean
clean:
	make -C src clean
	make -C tests clean
	rm -f $(EXECUTABLE)
