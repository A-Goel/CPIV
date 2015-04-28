all: main

main: test.o LFSR.o main.o
	g++ -o ps2a test.o LFSR.o -lboost_unit_test_framework
	g++ -o main main.o LFSR.o

main.o: main.cpp LFSR.hpp
	g++ -c main.cpp -Wall -Werror -ansi -pedantic

test.o: test.cpp LFSR.hpp
	g++ -c test.cpp -Wall -Werror -ansi -pedantic

LFSR.o: LFSR.cpp LFSR.hpp
	g++ -c LFSR.cpp -Wall -Werror -ansi -pedantic

clean:
	rm *.o *~ ps2a main
