all: run

src:
	javac -d build *.java

run: src
	clear
	@cd build; java InterfaceSQL

clean:
	rm -f build/*
