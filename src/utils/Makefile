all : main.cpp utils.o
	g++ -Wall -D _DEBUG main.cpp utils.o

lib : utils.o
	ar r utils.a utils.o

utils.o : utils.h utils.cpp
	g++ -c utils.cpp
clean:
	rm -rf *.o ./a.out

