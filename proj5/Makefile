CC = gcc 
CXXFLAGS = -std=c++11 -Wall -pedantic
all: clean proj5.x

proj5.x: passserver.cpp proj5.cpp
	g++ -std=c++11 passserver.cpp proj5.cpp -o proj5.x -lcrypt

clean:
	rm -f *.o *.x 
