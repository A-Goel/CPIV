/* 
 * File:   main.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This program aligns two DNA sequence std::strings of letters A, C, G,
 * and T with dynamic programming.
 */

#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For output formatting
#include <algorithm>
#include "ED.hpp" // Header file with dynamic programming class

int main() {
    
    std::string sequence1, sequence2;
    int best_score;
    std::cin >> sequence1;
    std::cin >> sequence2;
    
    sf::Clock clock;
    sf::Time t;    
    
    EditDistance DynamicMatrix(sequence1,sequence2);
    best_score = DynamicMatrix.OptDistance();
    std::cout << "Edit distance = " << best_score << std::endl;
	std::cout << DynamicMatrix.alignSequences();
    //std::cout << DynamicMatrix.alignSequences() << std::endl;
    //std::cout << "Edit distance = " << best_score << std::endl;
    
    t = clock.getElapsedTime();
    std::cout << "\nExecution time is " << t.asSeconds()
            << " seconds\n" << std::endl;
    
    return 0;
    
}
