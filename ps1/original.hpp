/* 
 * File:   original.hpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * Class structure for Stairs.
 */

#ifndef ORIGINAL_HPP_
#define ORIGINAL_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Stairs : public sf::Drawable {
public:
    Stairs(int recursion_depth, int window_width);
    sf::Vector2f midpoint(sf::Vector2f point1, sf::Vector2f point2);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void makeSquares(int level, sf::Vector2f point1, sf::Vector2f point2,
        sf::Vector2f point3, sf::Vector2f point4); // Recursively create squares
private:
    int _depth;
    int _width;
    vector<sf::ConvexShape> _squares; // Vector storing squares to draw
};

#endif /* ORIGINAL_HPP_ */
