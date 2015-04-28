/* 
 * File:   mainoriginal.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This application reads in two integers for depth and width to create
 * squares recursively to display on the window, resembling a staircase.
 * If the recursion depth is high enough it'll start to look like a
 * triangle.
 * 
 * >>> SOURCES
 * - Mostly I went by the documentation for the ConvexShape class:
 *   http://www.sfml-dev.org/documentation/2.0/classsf_1_1ConvexShape.php
 * - The idea of integrals, calculating an area below a function from
 *   adding a bunch of rectangles as the width of them approaches zero,
 *   made me want to try imitating an integral for a triangle.
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream> // For converting command line arg to integer
#include <string>
#include <iomanip> // For output formatting
#include <cmath> // For sqrt
#include "original.hpp" // Header for Stairs class

using namespace std;

int usage(){
    cout << "Usage:\n\toriginal <depth> <window_width>\n" << endl;
    cout << "Example:\n\toriginal 5 600\n" << endl;
    return 0; // Returns an error code of 0 after displaying sample input
}

int main(int argc, char* argv[]) {

    /**********
     * Parse command line arguments for recursion depth and window width.
     **********/

    // Three arguments: Application name, recursion depth, and window width.
    if (argc != 3) {
        cerr << "\nYou must specify only two arguments." << endl;
        return usage();
    }

    // Initialize variables to store recursion depth and width.
    int depth, width;

    // Check first argument (depth) is a valid number.
    istringstream arg_depth(argv[1]);
    if (!(arg_depth >> depth)) {
        cerr << "\n'" << argv[1] << "' is not a valid number." << endl;
        return usage();
    }
    if (depth < 0) {
        cerr << "\n'" << argv[1] << "' negative recursion depth." << endl;
        return usage();
    } else if (depth > 10) {
        cerr << "\n'" << argv[1] << "' recursion depth is overkill." << endl;
        return usage();
    }

    // Check second argument (width) is a valid number.
    istringstream arg_width(argv[2]);
    if (!(arg_width >> width)) {
        cerr << "\n'" << argv[2] << "' is not a valid number." << endl;
        return usage();
    }
    if (width < 0) {
        cerr << "\n'" << argv[2] << "' negative window width." << endl;
        return usage();
    } else if (width < 100) {
        cerr << "\n'" << argv[2] << "' too small, try at least 100." << endl;
        return usage();
    }

    /**********
     * Here we create a square window, where height is the width.
     * Stairs object stores the squares to draw out to screen.
     **********/

    double height = width;
    sf::RenderWindow window(sf::VideoMode(width, height), "Staircase");
    window.setFramerateLimit(30);
    sf::Event event;
    Stairs staircase(depth, width);
    
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }
        window.clear(sf::Color::Black);
        window.draw(staircase);
        window.display();
    }
    
}
