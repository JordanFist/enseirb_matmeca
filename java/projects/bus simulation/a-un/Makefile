all: build run

build: src tst

TEST_CLASS = tec.TestJauge tec.TestPosition tec.TestAutobus tec.TestPassagerStandard tec.TestPassagerIndecis tec.TestPassagerStresse tec.TestIntegration

.PHONY:src
src:
	javac -d build src/*.java

.PHONY:tst
tst:
	javac -d build/ -cp build/ tst/*.java

.PHONY:run
run:
	@cd build/; java -ea Simple
	@cd build/; java -ea tec/LancerTests ${TEST_CLASS}

.PHONY:clean
clean:
	rm -rf build/*
