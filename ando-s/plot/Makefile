CXXFLAGS=-Wall -Wextra -Wno-sign-compare -std=c++11

all: main

test: main
	./main 1 2 3 | sh -v

run: main
	./main ${ID} | sh -v

clean:
	rm -f main tmp/* img/*
