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
 * - Olga Lepsky helped me understand how I could do a conversion
 *   from distance to pixel. Basically, how many distance units are
 *   in a pixel? This provides a rate of conversion.
 * - Fred Martin for explaining the universe radius and its connection
 *   to the SFML window.
 * - Fred Martin for explaining stdin and the operator for "piping in"
 *   the input file with the "<" symbol.
 * - Fred Martin introduced some of the physics, and Willie Boag
 *   clarified the calculations for obtaining the new velocities
 *   and positions for the body objects -- especially net forces since
 *   each body is affected by the forces of all the other bodies.
 */

#include <iostream>
#include <string>
#include <vector>
#include "body.hpp"

/**********
 * CONSTRUCTORS AND DESTRUCTOR
 **********/

Body::Body()
{}

Body::Body(double x, double y, double x_vel, double y_vel, double mass,
        std::string img_file) :
_x_coordinate(x), _y_coordinate(y), _x_velocity(x_vel), _y_velocity(y_vel),
_mass(mass), _image_file(img_file)
{ setImage(_image_file); }

Body::~Body()
{}

/**********
 * OVERLOADED INPUT AND OUTPUT STREAM OPERATORS
 **********/

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
    body.setImage(body._image_file); // Set input image as sprite to draw.
    
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

/**********
 * MUTATORS
 **********/

void Body::setImage(std::string image_name)
{
    _image_file = "files/" + image_name;
    _image.loadFromFile(_image_file);
    _image_texture.loadFromImage(_image);
    _image_sprite.setTexture(_image_texture);
}

void Body::setWindowSize(int window_size)
{ _window_size = window_size; }

void Body::setUniverseRadius(double univ_radius)
{ _universe_radius = univ_radius; }

void Body::calculate_X_acceleration(double net_forces)
{ _x_acceleration = net_forces / _mass; }

void Body::calculate_Y_acceleration(double net_forces)
{ _y_acceleration = net_forces / _mass; }

void Body::step(double seconds)
{

    double new_x_velocity, new_y_velocity;
    double new_x_position, new_y_position;
    
    // Calculate the new velocities and positions.
    new_x_velocity = _x_velocity + (_x_acceleration * seconds);
    new_y_velocity = _y_velocity + (_y_acceleration * seconds);
    new_x_position = _x_coordinate + (new_x_velocity * seconds);
    new_y_position = _y_coordinate + (new_y_velocity * seconds);
 
    // Save the new velocities and positions into the Earth body object.
    _x_velocity = new_x_velocity;
    _y_velocity = new_y_velocity;
    _x_coordinate = new_x_position;
    _y_coordinate = new_y_position;

}

/**********
 * ACCESSORS
 **********/

double Body::get_X_pos()
{ return _x_coordinate; }

double Body::get_Y_pos()
{ return _y_coordinate; }

double Body::get_Mass()
{ return _mass; }

/**********
 * DRAWING
 **********/

sf::Vector2f Body::distance_to_pixel() const
{
    
    /*
     The radius goes from the center of the window to the side, so
     dividing the radius by half the window's size will give us a distance
     value per pixel. The meter_per_pixel value allows us to divide the
     distance by this value to directly get the pixel location. 
     */
    double meter_per_pixel = _universe_radius / (_window_size / 2.0);
    double x_pixel = (_window_size / 2.0) + (_x_coordinate / meter_per_pixel);
    double y_pixel = (_window_size / 2.0) - (_y_coordinate / meter_per_pixel);
    return sf::Vector2f(x_pixel, y_pixel); // Return pixel coordinates.
    
}

void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    /*
     Since this is a const function, we can't modify the original
     object's sprite. Make a new sprite that holds the same image
     but is able to get its position set in pixels.
     */
    sf::Sprite image_in_pixels = _image_sprite;
    image_in_pixels.setPosition( distance_to_pixel() );
    target.draw(image_in_pixels); 
    
}
