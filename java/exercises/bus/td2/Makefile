all: build run

build:
	javac TestJauge.java
	javac TestPosition.java

	javac Autobus.java
	javac TestAutobus.java

	javac Passager.java
	javac TestPassagerStandard.java

run:
	java -ea TestJauge
	java -ea TestPosition
	java -ea TestAutobus
	java -ea TestPassagerStandard

.PHONY:clean
clean:
	rm -f *.class
