all: main

main: main.o body.o
	g++ -o NBody main.o body.o -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp body.hpp
	g++ -c main.cpp -Wall -Werror -ansi -pedantic

body.o: body.cpp body.hpp
	g++ -c body.cpp -Wall -Werror -ansi -pedantic

clean:
	rm *.o *~ NBody
