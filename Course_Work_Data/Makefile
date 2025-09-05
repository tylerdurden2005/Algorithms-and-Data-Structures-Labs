all: main Tests clean
main: TrieStock.o CLI.o main.o
	g++ TrieStock.o CLI.o main.o -o main
Tests: TrieStock.o Tests.o
	g++ TrieStock.o Tests.o -lgtest -o Tests
TrieStock.o: modules/TrieStock.h modules/TrieStock.cpp
	g++ -c modules/TrieStock.cpp
CLI.o: modules/CLI.h modules/TrieStock.h modules/CLI.cpp
	g++ -c modules/CLI.cpp
main.o: main.cpp modules/CLI.h
	g++ -c main.cpp
Tests.o: Tests.cpp modules/TrieStock.h
	g++ -c Tests.cpp
clean:
	rm -rf *.o
