CPPFLAGS= -Wall -Wextra -pedantic

all:test.cpp Deque.hpp
	g++ $(CPPFLAGS) test.cpp Deque.hpp -O4 -ldl -std=c++17

run:all
	./a.out

checkmem:all
	valgrind ./a.out
	# Insert command to run the executable with valgrind

clean:a.out
	rm a.out Deque.hpp.gch
	# Insert command to clean object files, executables
