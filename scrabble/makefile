scrabble: main.o scrabble.o
	g++ -Wall -g main.o scrabble.o -o scrabble

scrabble.o: scrabble.cpp scrabble.h
	g++ -Wall -g -c scrabble.cpp

main.o: main.cpp scrabble.h
	g++ -Wall -g -c main.cpp

clean:
	rm -f *.o scrabble
