/* 
 * File:   main.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * Simple output statements to test the output operator for LFSR.
 */

#include <iostream>
#include <string>
#include <vector>
#include "LFSR.hpp"

int main(int argc, char** argv) {
    
    LFSR l("00111", 2);
    // This should return 198
    std::cout << "Current register value is: '" << l << "'" << std::endl;
    std::cout << "With eight steps, generated: '" << l.generate(8) << "'" << std::endl;
    std::cout << "Current register value is: '" << l << "'" << std::endl;

    return 0;
}
