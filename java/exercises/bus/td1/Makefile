all: build run

build:
	javac TestJauge.java
	javac TestPosition.java

run:
	java -ea TestJauge
	java -ea TestPosition

.PHONY:clean
clean:
	rm -f TestJauge.class
	rm -f TestPosition.class