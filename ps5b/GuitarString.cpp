// Copyright 2015 Roy Van Liew for 91.204 Computing IV
// * >>> SOURCES
// * - Fred Martin described some of these functions in class.

// C libraries
#include <stdint.h>
#include <math.h>

// C++ standard libraries
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

// My headers
#include "GuitarString.hpp"

GuitarString::GuitarString(double frequency) {
    int buffer_size = ceil(44100.0 / frequency);
    _rb = new RingBuffer(buffer_size);
    _tic_count = 0;
    pluck();  // Fill buffer with random numbers
}

GuitarString::GuitarString(std::vector<sf::Int16> init) {
    // Assume that this vector is full of samples already.
    _rb = new RingBuffer(static_cast<int>(init.size()));
    (*_rb).set_buffer(init);
    _tic_count = 0;
}

GuitarString::~GuitarString() {
    delete _rb;  // Delete the Pointer to the RingBuffer object
}

void GuitarString::pluck() {
    // Fills guitar string's ring buffer with random numbers
    int i;
    (*_rb).empty();  // Empty previous buffer
    sf::Int16 random_noise;
    for (i = 0; i < (*_rb).get_capacity(); i++) {
        random_noise = (sf::Int16)(rand() & 0xffff);  // NOLINT
        (*_rb).enqueue(random_noise);
    }
}

void GuitarString::tic() {
    sf::Int16 deleted_sample, first_sample;
    double decay_avg;
    deleted_sample = (sf::Int16)(*_rb).dequeue();
    first_sample = sample();
    decay_avg = 0.996 * ((deleted_sample + first_sample) / 2.0);
    (*_rb).enqueue((int16_t) decay_avg);
    _tic_count++;
}

sf::Int16 GuitarString::sample() {
    return (sf::Int16)(*_rb).peek();
}

int GuitarString::time() {
    return _tic_count;
}
