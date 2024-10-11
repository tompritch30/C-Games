correct: main.o correct.o
	g++ -Wall -g main.o correct.o -o correct

main.o: main.cpp correct.h
	g++ -Wall -g main.cpp -c main.o

correct.o: correct.cpp correct.h
	g++ -Wall -g correct.cpp -c correct.o

clean:
	rm -f *.o correct
