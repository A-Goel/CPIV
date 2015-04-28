all: main

main: test.o RingBuffer.o
	g++ -o ps5a test.o RingBuffer.o -lboost_unit_test_framework

test.o: test.cpp RingBuffer.hpp
	g++ -c test.cpp -Wall -Werror -ansi -pedantic

LFSR.o: RingBuffer.cpp RingBuffer.hpp
	g++ -c RingBuffer.cpp -Wall -Werror -ansi -pedantic

clean:
	rm *.o *~ ps5a
