EXECUTABLE=main
EXE=project

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE):
	make -C achievement_2 
	@cp achievement_2/$(EXECUTABLE) ./$(EXE)

.PHONY: test
test:
	make -C achievement_2 test

.PJONY: clean
clean:
	make -C achievement_2 clean
	rm -f $(EXE)
