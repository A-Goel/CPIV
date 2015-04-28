/* 
 * File:   body.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This file implements the celestial body object for displaying in the
 * SFML window.
 * 
 * >>> SOURCES
 * - Olga Lepsky for walking by in Olsen 2nd floor around noon on
 *   Wednesday, and helped me understand how I could do a conversion
 *   from distance to pixel. Basically, how many distance units are
 *   in a pixel? This provides a rate of conversion!
 * - Fred Martin for explaining the universe radius and its connection
 *   to the SFML window.
 * - Fred Martin for explaining stdin and the operator for "piping in"
 *   the input file with the "<" symbol.
 */

#include <iostream>
#include <string>
#include <vector>
#include "body.hpp"

Body::Body()
{}

// Constructor initializing body
Body::Body(double x, double y, double x_vel, double y_vel, double mass,
        std::string img_file) :
_x_coordinate(x), _y_coordinate(y), _x_velocity(x_vel), _y_velocity(y_vel),
_mass(mass), _image_file(img_file)
{ setImage(_image_file); }

Body::~Body()
{}

// Overloaded input operator
std::istream& operator>>(std::istream &in, Body& body)
{
    
    // Call cin six times to read across a body information line
    in >> body._x_coordinate;
    in >> body._y_coordinate;
    in >> body._x_velocity;
    in >> body._y_velocity;
    in >> body._mass;
    in >> body._image_file;
    body.setImage(body._image_file); // Set the input image as sprite to draw.
    
    return in;
    
}

std::ostream& operator <<(std::ostream &out, Body &body)
{
    
    // Prints out the body's properties.
    out << body._x_coordinate << " ";
    out << body._y_coordinate << " ";
    out << body._x_velocity << " ";
    out << body._y_velocity << " ";
    out << body._mass << " ";
    out << body._image_file << std::endl;
    
    return out;
    
}

void Body::setImage(std::string image_name)
{
    _image_file = image_name;
    _image.loadFromFile(_image_file);
    _image_texture.loadFromImage(_image);
    _image_sprite.setTexture(_image_texture);
}

void Body::setWindowSize(int window_size)
{ _window_size = window_size; }

void Body::setUniverseRadius(double univ_radius)
{ _universe_radius = univ_radius; }

sf::Vector2f Body::distance_to_pixel() const
{
    
    /*
     We need a way to convert the distance numbers to pixel values.
     Assuming a square window, the center of the universe (0,0)
     Is half the window size. The radius goes from the center of the
     window to the side, so dividing the radius by half the window's
     size will give us a distance value per pixel. The
     meter_per_pixel value allows us to divide the distance by this value
     to directly get the pixel location. 
     */   
    double meter_per_pixel = _universe_radius/(_window_size/2.0);
    double x_pixel, y_pixel; // Stores conversion of distance to pixel.
    
    // Get pixel coordinates for x. If positive distance value, add to
    // center; otherwise, subtract from center.
    if(_x_coordinate >= 0.0)
        x_pixel = (_window_size/2.0) + (_x_coordinate/meter_per_pixel);
    else
        x_pixel = (_window_size/2.0) - (_x_coordinate/meter_per_pixel);
    
    // Get pixel coordinates for y. Positive distance subtracts from
    // center to make sprite go up on window.
    if(_y_coordinate >= 0.0)
        y_pixel = (_window_size/2.0) - (_y_coordinate/meter_per_pixel);
    else
        y_pixel = (_window_size/2.0) + (_y_coordinate/meter_per_pixel);
    
    return sf::Vector2f(x_pixel,y_pixel); // Return pixel coordinates.
    
}

void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
    // Since this is a const function, we can't modify the original
    // object's sprite. Make a new sprite that holds the same image
    // but is able to get its position set in pixels.
    sf::Sprite image_in_pixels = _image_sprite;
    image_in_pixels.setPosition( distance_to_pixel() );
    target.draw(image_in_pixels); 
    
}
