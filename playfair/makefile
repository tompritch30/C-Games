playfair: playfair.o main.o
	g++ -Wall -g playfair.o main.o -o playfair

main.o: main.cpp playfair.h
	g++ -Wall -g -c main.cpp

playfair.o: playfair.cpp playfair.h
	g++ -Wall -g -c playfair.cpp

clean:
	rm -f *.o playfair
