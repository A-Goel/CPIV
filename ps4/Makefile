all: main

main: main.o ED.o
	g++ -g -O3 -o ED main.o ED.o -lsfml-system

main.o: main.cpp ED.hpp
	g++ -g -O3 -c main.cpp -Wall -Werror -ansi -pedantic

ED.o: ED.cpp ED.hpp
	g++ -g -O3 -c ED.cpp -Wall -Werror -ansi -pedantic

clean:
	rm *.o *~ ED
