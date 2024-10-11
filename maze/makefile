maze: maze.o main.o
	g++ -Wall -g maze.o main.o -o maze

main.o: main.cpp maze.h
	g++ -Wall -g -c main.cpp

maze.o: maze.cpp maze.h
	g++ -Wall -g -c maze.cpp

clean:
	rm -f *.o maze
