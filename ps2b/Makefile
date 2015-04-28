all: main

main: LFSR.o PhotoMagic.o
	g++ -o PhotoMagic PhotoMagic.o LFSR.o -lsfml-graphics -lsfml-window -lsfml-system

PhotoMagic.o: PhotoMagic.cpp LFSR.hpp
	g++ -c PhotoMagic.cpp -Wall -Werror -ansi -pedantic

LFSR.o: LFSR.cpp LFSR.hpp
	g++ -c LFSR.cpp -Wall -Werror -ansi -pedantic

clean:
	rm *.o *~ PhotoMagic
