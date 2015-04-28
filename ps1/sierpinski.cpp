/* 
 * File:   sierpinski.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * Implementation of the Sierpinski class.
 */

#include <iostream>
#include <cmath>
#include "sierpinski.hpp"

Sierpinski::Sierpinski(int recursion_depth, int window_width) :
_depth (recursion_depth),_width (window_width)
{   
    
    // Set initial UPSIDE triangle coordinates.
    double height = (sqrt(3)/2.0) * double(_width);
    sf::Vector2f bottom_left = sf::Vector2f(0, height); // Bottom left corner
    sf::Vector2f bottom_right = sf::Vector2f(_width, height); // Bottom right
    sf::Vector2f top_middle = sf::Vector2f((_width/2), 0); // Middle top point
    
    // Create the upside-down triangles, calculated by midpoints.
    makeTriangles(_depth,bottom_left,bottom_right,top_middle);
    
}

sf::Vector2f Sierpinski::midpoint(sf::Vector2f point1, sf::Vector2f point2)
{
    return sf::Vector2f((point1.x + point2.x) / 2,  // Middle x-coordinate
                    (point1.y + point2.y) / 2); // Middle y-coordinate
}

void Sierpinski::makeTriangles(int level, sf::Vector2f point1,
    sf::Vector2f point2, sf::Vector2f point3)
{
    
    if( level == 0 )
        return;
    else {    
        
        // Midpoint is used to find coordinates of the upside down triangle.
        sf::Vector2f mid_1_2 = midpoint(point1,point2);
        sf::Vector2f mid_2_3 = midpoint(point2,point3);
        sf::Vector2f mid_1_3 = midpoint(point1,point3);
        
        // Set the following points in order for the upside-down triangle.
        sf::ConvexShape tri;
        tri.setPointCount(3);
        tri.setFillColor(sf::Color::Blue);
        tri.setPoint(0, mid_1_2); // Top left corner
        tri.setPoint(1, mid_2_3); // Top right corner
        tri.setPoint(2, mid_1_3); // Bottom middle point
        _triangles.push_back(tri); // Store this triangle to be drawn later.
        
        // Do calls to make the upside-down triangles for two corners and top.
        makeTriangles((level-1),point1,mid_1_2,mid_1_3); // Bottom-left
        makeTriangles((level-1),mid_1_2,point2,mid_2_3); // Top
        makeTriangles((level-1),mid_1_3,mid_2_3,point3); // Bottom-right
        
    }
}

// Allows passing Sierpinski object to window's draw function in main.
void Sierpinski::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
    // Initialize counter variables.
    int i;
    int numOfTriangles = _triangles.size();
    
    // Iterate through vector of triangles created from makeTriangles().
    for( i = 0; i < numOfTriangles; i++)
        target.draw(_triangles[i]);
    
}