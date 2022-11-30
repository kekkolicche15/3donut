all: compile run

compile:
	mkdir -p bin
	gcc ./source/main.c -o ./bin/main -lm

run:
	./bin/main

clean:
	rm ./bin/main
