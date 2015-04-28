/* 
 * File:   sierpinski.hpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * Class structure for Sierpinski.
 */

#ifndef SIERPINSKI_HPP_
#define SIERPINSKI_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Sierpinski : public sf::Drawable {
public:
    Sierpinski(int recursion_depth, int window_width);
    sf::Vector2f midpoint(sf::Vector2f point1, sf::Vector2f point2);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void makeTriangles(int level, sf::Vector2f point1, sf::Vector2f point2,
        sf::Vector2f point3); // Recursively create triangles, stored in vector
private:
    int _depth;
    int _width;
    vector<sf::ConvexShape> _triangles; // Vector to iterate through for draw
};

#endif /* SIERPINSKI_HPP_ */
