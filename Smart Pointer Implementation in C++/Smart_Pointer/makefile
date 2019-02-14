CPPFLAGS= -Wall -Wextra -pedantic -g -pthread

all: SharedPtr.hpp SharedPtr_test.cpp
	g++ -std=c++11 $(CPPFLAGS) SharedPtr_test.cpp -o SharedPtr

run:all
	./SharedPtr

checkmem: all
	valgrind ./SharedPtr

clean:
	rm SharedPtr 
