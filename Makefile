all: compile run

compile:
	gcc ./source/main.c -o ./bin/main -lm

run:
	./bin/main

clean:
	rm ./bin/main
