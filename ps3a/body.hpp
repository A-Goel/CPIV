/* 
 * File:   body.hpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * Class structure for the celestial Body class.
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Body : public sf::Drawable {
    
public:
    
    // Constructors and Destructor
    Body();
    Body(double x, double y, double x_vel, double y_vel, double mass,
            std::string img_file);
    ~Body();
    
    // Overloaded stream operators
    friend std::ostream& operator<<(std::ostream &out, Body &body);
    friend std::istream& operator>>(std::istream &in, Body& body);

    // Mutators
    void setImage(std::string image_name);
    void setWindowSize(int window_size);
    void setUniverseRadius(double univ_radius);

    // Pixel conversion and draw
    sf::Vector2f distance_to_pixel() const; // const since draw is const
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    double _x_coordinate;
    double _y_coordinate;
    double _x_velocity;
    double _y_velocity;
    double _mass;
    double _universe_radius; // Needed for pixel conversion
    int _window_size; // Assuming a square window, needed for pixel conversion
    std::string _image_file;
    sf::Image _image;
    sf::Texture _image_texture;
    sf::Sprite _image_sprite;

};
