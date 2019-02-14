CPPFLAGS= -Wall -Wextra -pedantic -g

all:IteratorsBase.inl IteratorsRecursive.inl Array.hpp
	g++ -std=c++11 $(CPPFLAGS) Test_Array.cpp

run:all
	./a.out

checkmem:all
	valgrind ./a.out

clean:
	rm a.out
