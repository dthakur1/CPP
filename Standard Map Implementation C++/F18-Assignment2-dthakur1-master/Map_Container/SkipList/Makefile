all: SkipListTest.cpp SkipListTest.hpp SkipListTest.inl
	g++ $(CPPFLAGS) --std=c++17 SkipListTest.cpp -o SkipListTest

mem:all
	valgrind ./SkipListTest

run:all
	./SkipListTest

clean:
	rm SkipListTest
