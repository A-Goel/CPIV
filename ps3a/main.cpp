/* 
 * File:   main.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This application reads in an input universe file (e.g. planets.txt)
 * that contains information about the bodies' properties and image
 * files to display in the window. First we determine the window's size
 * and assume it is a square window for simplicity.
 * 1.) Determine window properties, such as size
 * 2.) Read in number of celestial bodies and universe radius from file
 * 3.) Create vector of Body objects, which will be used later
 * 4.) Since we've read in the first two lines of the file, the rest of
 *     the lines are body property lines. For each Body, read in this
 *     information and also give the Bodies window size & universe radius.
 * 5.) Display each Body out to the window.
 * 
 * Sources are listed in bodyfunctions.cpp
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream> // File stream
#include <sstream> // For converting command line arg to integer
#include <string>
#include <iomanip> // For output formatting
#include <cmath> // For sqrt
#include "body.hpp"

int main(int argc, char* argv[]) {
    
    // Window size is determined in main. Assume a square window.
    int win_size = 600;
    sf::RenderWindow window(sf::VideoMode(win_size, win_size), "Solar System");
    window.setFramerateLimit(1);
    sf::Event event;
    
    // Get number of celestial bodies and universe radius from file.
    int i, numOfBodies;
    double radius;
    std::cin >> numOfBodies;
    std::cin >> radius;
    
    // Create Number of Bodies based on count from file
    std::vector<Body*> Bodies;
    for(i=0; i<numOfBodies; i++)
        Bodies.push_back(new Body);
    
    // Along with the six properties on each line,
    // what the bodies also need are window size and universe radius.
    for(i=0; i<numOfBodies; i++){
        std::cin >> (*Bodies[i]);
        (*Bodies[i]).setWindowSize(win_size);
        (*Bodies[i]).setUniverseRadius(radius);
    }
    
    // In this while loop we draw each celestial body.
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }
        window.clear(sf::Color::Black);
        for(i=0; i<numOfBodies; i++)
            window.draw((*Bodies[i]));
        window.display();
    }   
    
    // Debug: Print out values in the bodies.
    for(i=0; i<numOfBodies; i++)
        std::cout << (*Bodies[i]);
    
    return 0;
    
}

