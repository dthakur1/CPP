CPPFLAGS= -Wall -Wextra -pedantic

all: test minimal test-kec test-scaling morseex

run: test-scaling
	./test-scaling	

test: test.cpp Map.hpp Iterator.inl Map.inl
	g++ $(CPPFLAGS) -std=c++17  test.cpp -o test

minimal: minimal.cpp Map.hpp Iterator.inl Map.inl
	g++ $(CPPFLAGS) -std=c++17  minimal.cpp -o minimal

test-kec: test-kec.cpp Map.hpp Iterator.inl Map.inl
	g++ $(CPPFLAGS) -std=c++17  test-kec.cpp -o test-kec

test-scaling: test-scaling.cpp Map.hpp Iterator.inl Map.inl
	g++ $(CPPFLAGS) -std=c++17  test-scaling.cpp -o test-scaling

morseex: morseex.cpp Map.hpp Iterator.inl Map.inl
	g++ $(CPPFLAGS) -std=c++17  morseex.cpp -o morseex


checkmem:test-kec
	valgrind ./test-kec

clean:
	# Insert command to clean object files, executables
