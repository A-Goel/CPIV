/* 
 * File:   main.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This application reads in two integers for depth and width to create
 * triangles recursively for displaying a Sierpinski Triangle on the window.
 * 
 * >>> SOURCES
 * - Fred Martin himself for discussing the window height calculation,
 *   midpoint idea and mapping coordinates. He also got me started
 *   with drawing triangles in the class definition.
 * - http://stackoverflow.com/questions/21294413/sfml-c-drawing-into-renderwindow-pure-virtual-function-runtime-failure
 * - Above link is what made me implement a vector of triangle shapes
 *   so those triangles could be printed later.
 * - http://stackoverflow.com/questions/2797813/convert-c-argument-to-int
 * - Above link is what inspired the error-checking design for when I
 *   am parsing the user's arguments to the application.
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream> // For converting command line arg to integer
#include <string>
#include <iomanip> // For output formatting
#include <cmath> // For sqrt
#include "sierpinski.hpp" // Header for Sierpinski class

using namespace std;

int usage(){
    cout << "Usage:\n\tsierpinski <depth> <window_width>\n" << endl;
    cout << "Example:\n\tsierpinski 3 600\n" << endl;
    return 0; // Returns an error code of 0 after displaying sample input
}

int main(int argc, char* argv[]) {

    /**********
     * Parse command line arguments for recursion depth and window width.
     **********/

    // There should be 3 arguments: Program, recursion depth, and window width.
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
     * Here we initialize the window with the passed width, calculate
     * its height, and then create Sierpinski object for the triangles.
     **********/

    double height = (sqrt(3) / 2.0) * (double)width;
    sf::RenderWindow window(sf::VideoMode(width, height), "Sierpinski");
    window.setFramerateLimit(30);
    sf::Event event;
    Sierpinski st(depth, width);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }
        window.clear(sf::Color::Black);
        window.draw(st);
        window.display();
    }
    
}
