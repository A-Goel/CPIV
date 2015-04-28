all: main

main: GuitarHero.o RingBuffer.o GuitarString.o GStest.o
	g++ -Wall GuitarHero.o RingBuffer.o GuitarString.o \
   -o GuitarHero -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window
	g++ GStest.o GuitarString.o RingBuffer.o -o GStest -lboost_unit_test_framework


GStest.o: GStest.cpp GuitarString.hpp
	g++ -c GStest.cpp -lboost_unit_test_framework

GuitarString.o: GuitarString.cpp GuitarString.hpp
	g++ -c GuitarString.cpp -Wall -Werror -ansi -pedantic

GuitarHero.o: GuitarHero.cpp GuitarString.hpp
	g++ -Wall -c GuitarHero.cpp -lsfml-system \
     -lsfml-audio -lsfml-graphics -lsfml-window

RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	g++ -c RingBuffer.cpp -Wall -Werror -ansi -pedantic

clean:
	rm *.o *~ ps5b GuitarHero GStest
