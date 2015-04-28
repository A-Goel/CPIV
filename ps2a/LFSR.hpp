/* 
 * File:   LFSR.hpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * Class structure for the LFSR class. Sources used to aid in this are
 * mentioned in LFSR.cpp
 */

#include <iostream>
#include <vector>

class LFSR {
public:
	LFSR(std::string seed, int tap);
	~LFSR();
	int step();
	int generate(int k); // Creates a new bit sequence through step() calls
	friend std::ostream& operator<< (std::ostream &out, LFSR &lfsr);

private:
	std::vector<int> _seed; // Represents the register of 1's and 0's
	int _tap; // Tap bit position for the XOR task in step()

};

