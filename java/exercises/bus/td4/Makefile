all: build run

build: src tst

.PHONY:src
src:
	javac -d build src/*.java

.PHONY:tst
tst:
	javac -d build/ -cp build/ tst/*.java

.PHONY:run
run:
	@cd build/; java -ea tec/TestJauge
	@cd build/; java -ea tec/TestPosition
	@cd build/; java -ea tec/TestAutobus
	@cd build/; java -ea tec/TestPassagerStandard
	@cd build/; java -ea Simple

.PHONY:clean
clean:
	rm -rf build/*
