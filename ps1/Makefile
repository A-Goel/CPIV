all: main

main: main.o sierpinski.o mainoriginal.o original.o
	g++ -o sierpinski main.o sierpinski.o -lsfml-graphics -lsfml-window -lsfml-system
	g++ -o original mainoriginal.o original.o -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp sierpinski.hpp
	g++ -c main.cpp -Wall -Werror -ansi -pedantic

sierpinski.o: sierpinski.cpp sierpinski.hpp
	g++ -c sierpinski.cpp -Wall -Werror -ansi -pedantic

mainoriginal.o: mainoriginal.cpp original.hpp
	g++ -c mainoriginal.cpp -Wall -Werror -ansi -pedantic

original.o: original.cpp original.hpp
	g++ -c original.cpp -Wall -Werror -ansi -pedantic

clean:
	rm *.o sierpinski original *~
