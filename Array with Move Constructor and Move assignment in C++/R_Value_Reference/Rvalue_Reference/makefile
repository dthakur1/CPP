CPPFLAGS= -Wall -Wextra -pedantic -g

all:Array_test.cpp Array.hpp MyInt.cpp MyInt.hpp
	g++ $(CPPFLAGS) -std=c++11 Array_test.cpp MyInt.cpp -o RvalRef

run:all
	./RvalRef

checkmem:all
	valgrind ./RvalRef

clean:
	rm RvalRef
	# Insert command to clean object files, executables
