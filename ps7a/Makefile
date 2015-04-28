all: main

main: main.o tracker.o
	g++ -o ps7a main.o tracker.o -lboost_regex -lboost_date_time

main.o: main.cpp tracker.hpp
	g++ -c main.cpp -Wall -Werror -ansi -pedantic

tracker.o: tracker.cpp tracker.hpp
	g++ -c tracker.cpp -Wall -Werror -ansi -pedantic

clean:
	rm *.o *~ ps7a
