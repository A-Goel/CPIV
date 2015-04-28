all: main

main: mmtest.o MarkovModel.o TextGenerator.o
	g++ -o mmtest mmtest.o MarkovModel.o -lboost_unit_test_framework
	g++ -o TextGenerator TextGenerator.o MarkovModel.o

mmtest.o: mmtest.cpp MarkovModel.hpp
	g++ -c mmtest.cpp -Wall

MarkovModel.o: MarkovModel.cpp MarkovModel.hpp
	g++ -c MarkovModel.cpp -Wall

TextGenerator.o: TextGenerator.cpp MarkovModel.hpp
	g++ -c TextGenerator.cpp

clean:
	rm *.o *~ mmtest TextGenerator
