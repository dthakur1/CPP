CPPFLAGS= -Wall -Wextra -pedantic -g

all:Interpolate.hpp
	g++ -std=c++17 $(CPPFLAGS) Interpolate.cpp

run:all
	./a.out

checkmem:all
	valgrind ./a.out

clean:
	rm a.out
