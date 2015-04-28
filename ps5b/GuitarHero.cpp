// Copyright 2015 Roy Van Liew for 91.204 Computing IV
// * >>> SOURCES
// * - Fred Martin gave an introduction to some music theory regarding
// *   the algorithm for different notes. He also gave the original
// *   GuitarHeroLite code which I modified here.
// * - Willie Boag clarified how the SoundBuffer and Sound objects
// *   related to each other and explained why the arrangement of
// *   letters made sense (it represents a piano).

// C libraries, SFML libraries
#include <math.h>
#include <limits.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

// C++ libraries
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <map>

// My headers
#include "GuitarString.hpp"

// Global variables
#define CONCERT_A 440.0
#define SAMPLES_PER_SEC 44100
#define NOTES 37

std::vector<sf::Int16> makeSamplesFromString(GuitarString gs) {
    std::vector<sf::Int16> samples;

    gs.pluck();
    int duration = 8;  // seconds
    int i;
    for (i = 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs.tic();
        samples.push_back(gs.sample());
    }

    return samples;
}

int main() {
    // keyboard is an STL map that turns an SFML key into an index.
    // "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' "
    std::map<int, int> keyboard;
    keyboard[sf::Keyboard::Q] = 0;
    keyboard[sf::Keyboard::Num2] = 1;
    keyboard[sf::Keyboard::W] = 2;
    keyboard[sf::Keyboard::E] = 3;
    keyboard[sf::Keyboard::Num4] = 4;
    keyboard[sf::Keyboard::R] = 5;
    keyboard[sf::Keyboard::Num5] = 6;
    keyboard[sf::Keyboard::T] = 7;
    keyboard[sf::Keyboard::Y] = 8;
    keyboard[sf::Keyboard::Num7] = 9;
    keyboard[sf::Keyboard::U] = 10;
    keyboard[sf::Keyboard::Num8] = 11;
    keyboard[sf::Keyboard::I] = 12;
    keyboard[sf::Keyboard::Num9] = 13;
    keyboard[sf::Keyboard::O] = 14;
    keyboard[sf::Keyboard::P] = 15;
    keyboard[sf::Keyboard::Dash] = 16;
    keyboard[sf::Keyboard::LBracket] = 17;
    keyboard[sf::Keyboard::Equal] = 18;
    keyboard[sf::Keyboard::Z] = 19;
    keyboard[sf::Keyboard::X] = 20;
    keyboard[sf::Keyboard::D] = 21;
    keyboard[sf::Keyboard::C] = 22;
    keyboard[sf::Keyboard::F] = 23;
    keyboard[sf::Keyboard::V] = 24;
    keyboard[sf::Keyboard::G] = 25;
    keyboard[sf::Keyboard::B] = 26;
    keyboard[sf::Keyboard::N] = 27;
    keyboard[sf::Keyboard::J] = 28;
    keyboard[sf::Keyboard::M] = 29;
    keyboard[sf::Keyboard::K] = 30;
    keyboard[sf::Keyboard::Comma] = 31;
    keyboard[sf::Keyboard::Period] = 32;
    keyboard[sf::Keyboard::SemiColon] = 33;
    keyboard[sf::Keyboard::Slash] = 34;
    keyboard[sf::Keyboard::Quote] = 35;
    keyboard[sf::Keyboard::Space] = 36;

    /**********
     * From Fred's GuitarHeroLite file:
     * - We're reusing the freq and samples vars, but there are separate
     * copies of GuitarString, SoundBuffer, and Sound for each note.
     * - GuitarString is based on freq.
     * - samples vectors are generated from GuitarString.
     * - SoundBuffer is loaded from samples.
     * - Sound is set to SoundBuffer.
     **********/

    // Vectors related to the sound buffers
    std::vector<std::vector <sf::Int16> > samples;
    std::vector<GuitarString*> guitar_strings;
    std::vector<sf::Sound> sounds;
    std::vector<sf::SoundBuffer> sound_buffers;
    samples.resize(NOTES);
    sounds.resize(NOTES);
    sound_buffers.resize(NOTES);

    // Fill in the sound buffer objects
    int i;
    double freq;
    for (i = 0; i < NOTES; i++) {
        freq = CONCERT_A * pow(2, (i - 24) / 12.0);
        guitar_strings.push_back(new GuitarString(freq));

        samples[i] = makeSamplesFromString(*guitar_strings[i]);
        if (!sound_buffers[i].loadFromSamples(&samples[i][0],
                samples[i].size(), 2, SAMPLES_PER_SEC))
            throw std::runtime_error("sf::SoundBuffer: failed to load "
                    "from samples.");

        sounds[i].setBuffer(sound_buffers[i]);
    }
    // Create the window and then the user can play notes.
    sf::RenderWindow window(sf::VideoMode(300, 200), "SFML Guitar Hero Lite");
    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                // Close button closes the window.
                case sf::Event::Closed:
                    window.close();
                    break;

                // If a key is pressed, look up that key in our map
                // for the corresponding Sound Buffer index.
                case sf::Event::KeyPressed:
                    sounds[ keyboard[event.key.code] ].play();
                    break;

                default:
                    break;
            }

            window.clear();
            window.display();
        }
    }
    return 0;
}
