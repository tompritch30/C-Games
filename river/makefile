river: main.o river.o
	g++ -Wall -g river.o main.o -o river

main.o: main.cpp river.h
	g++ -Wall -g -c main.cpp

river.o: river.cpp river.h
	g++ -Wall -g -c river.cpp

clean:
	rm -f *.o river
