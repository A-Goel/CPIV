// Copyright 2015 Roy Van Liew for 91.204 Computing IV

// C libraries, and SFML libraries
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// C++ standard libraries
#include <vector>

// My headers
#include "RingBuffer.hpp"

class GuitarString {
 public:
    explicit GuitarString(double frequency);
    explicit GuitarString(std::vector<sf::Int16> init);
    ~GuitarString();
    void pluck();
    void tic();
    sf::Int16 sample();
    int time();

 private:
    RingBuffer* _rb;
    int _tic_count;
};
