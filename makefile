hw6: main.o
	g++ -o hw6 main.o

main.o: main.cpp LinkedBSearchTree.h
	g++ -std=c++17 -c main.cpp

clean:
	rm -f hw6 *.o