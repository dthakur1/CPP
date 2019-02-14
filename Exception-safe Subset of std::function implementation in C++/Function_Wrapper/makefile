CPPFLAGS= -Wall -Wextra -pedantic -g

all:Function_test.cpp Function.hpp
	g++ -std=c++14 $(CPPFLAGS) Function_test.cpp -o FuncWrap
	
run:all
	./FuncWrap
	
checkmem:all
	valgrind ./FuncWrap
	
clean:
	rm FuncWrap
	