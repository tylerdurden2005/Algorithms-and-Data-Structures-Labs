all: main Tests clean
main: Cut.o Merge.o Blocks.o main.o
	g++ Cut.o Merge.o Blocks.o main.o -o main
Tests: Cut.o Merge.o Blocks.o Tests.o
	g++ Cut.o Merge.o Blocks.o Tests.o -lgtest -pthread -o Tests
Cut.o: Modules/Cut.cpp Modules/Cut.h
	g++ -c Modules/Cut.cpp
Merge.o: Modules/Merge.cpp Modules/Merge.h Modules/Cut.h
	g++ -c Modules/Merge.cpp
Blocks.o: Modules/Blocks.cpp Modules/Merge.h Modules/Blocks.h
	g++ -c Modules/Blocks.cpp
main.o: main.cpp Modules/Blocks.h
	g++ -c main.cpp
Tests.o: Tests.cpp Modules/Blocks.h
	g++ -c Tests.cpp
clean:
	rm -rf *.o
