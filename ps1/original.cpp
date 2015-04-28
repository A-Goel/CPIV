/* 
 * File:   original.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * Implementation of the Stairs class for making a recursive staircase
 * composed of hollow white-outlined squares.
 */

#include <iostream>
#include <cmath>
#include "original.hpp"

Stairs::Stairs(int recursion_depth, int window_width) :
_depth (recursion_depth),_width (window_width)
{
    
    // Initial square coordinates
    double height = _width;
    sf::Vector2f pt1, pt2, pt3, pt4;
    pt1 = sf::Vector2f(0, height); // Bottom left corner
    pt2 = sf::Vector2f(0, (height/2.0)); // Top left corner
    pt3 = sf::Vector2f((_width/2.0), (height/2.0)); // Top right corner
    pt4 = sf::Vector2f((_width/2.0), height); // Bottom right corner
    
    // Make all the squares and add them to the vector to iterate in draw.
    makeSquares(_depth,pt1,pt2,pt3,pt4);
    
}

sf::Vector2f Stairs::midpoint(sf::Vector2f point1, sf::Vector2f point2)
{
    return sf::Vector2f((point1.x + point2.x) / 2,  // Middle x-coordinate
                    (point1.y + point2.y) / 2); // Middle y-coordinate
}

void Stairs::makeSquares(int level, sf::Vector2f point1, sf::Vector2f point2,
    sf::Vector2f point3, sf::Vector2f point4)
{
    
    if( level == 0 )
        return;
    else {    

        // Add the passed square to the vector of squares to draw later.
        sf::ConvexShape square;
        square.setPointCount(4);
        square.setPoint(0, point1); // Bottom left corner
        square.setPoint(1, point2); // Top left corner
        square.setPoint(2, point3); // Top right corner
        square.setPoint(3, point4); // Bottom right corner
        square.setFillColor(sf::Color::Transparent);
        square.setOutlineColor(sf::Color::White);
        square.setOutlineThickness(1);
        _squares.push_back(square);
        double half_value; // Half the square's width for offset calculations.

        // Points for the smaller square on top.
        half_value = (point3.x - point2.x) / 2.0; // Offset to subtract
        sf::Vector2f top_pt1, top_pt2, top_pt3, top_pt4;
        top_pt1 = sf::Vector2f(point2); // Bottom left corner
        top_pt2 = sf::Vector2f(point2.x,point2.y - half_value); // Top left corner, shift up
        top_pt3 = sf::Vector2f(point3.x - half_value, point3.y - half_value); // Top right corner, shift up
        top_pt4 = sf::Vector2f(point3.x - half_value, point3.y); // Bottom right corner

        // Points for the smaller square on the right.      
        half_value = (point4.x - point1.x) / 2.0; // Offset to add
        sf::Vector2f right_pt1, right_pt2, right_pt3, right_pt4;
        right_pt1 = sf::Vector2f(point4); // Bottom left corner
        right_pt2 = sf::Vector2f(midpoint(point3, point4)); // Top left corner
        right_pt3 = sf::Vector2f(midpoint(point3, point4)); // Top right corner
        right_pt3.x = right_pt3.x + half_value; // shift x value to the right
        right_pt4 = sf::Vector2f(point4.x + half_value, point4.y); // Bottom right corner

        // These recursions are done in the order: Top square, right square. 
        makeSquares((level - 1), top_pt1, top_pt2, top_pt3, top_pt4); // Top square
        makeSquares((level - 1), right_pt1, right_pt2, right_pt3, right_pt4); // Right square
        
    }
}

// Allows passing Stairs object to window's draw function in main.
void Stairs::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
    // Initialize counter variables.
    int i;
    int numOfSquares = _squares.size();
    
    // Iterate through vector of squares created from makeSquares().
    for( i = 0; i < numOfSquares; i++)
        target.draw(_squares[i]);
    
}