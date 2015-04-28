/* 
 * File:   main.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This application reads in an input universe file (e.g. planets.txt)
 * that contains information about the bodies' properties and image
 * files to display in the window. First we determine the window's size
 * and assume it is a square window for simplicity.
 * 1.) Determine window properties, such as size
 * 2.) Read in number of celestial bodies and universe radius from file
 * 3.) Create vector of Body objects, which will be used later
 * 4.) Since we've read in the first two lines of the file, the rest of
 *     the lines are body property lines. For each Body, read in this
 *     information and also give the Bodies window size & universe radius.
 * 5.) Display each Body out to the window, performing any necessary
 *     physics calculations.
 * 
 * Sources are listed in body.cpp
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream> // File stream
#include <sstream> // For converting command line arg to integer
#include <string>
#include <iomanip> // For output formatting
#include <cmath> // For sqrt
#include "body.hpp"

int usage() {
    std::cout << "Usage:\n\tNBody <time_limit> <time_delta> "
            "< <universe_file>\n" << std::endl;
    std::cout << "Example:\n\tNBody 157788000.0 25000.0 "
            "< planets.txt\n" << std::endl;
    return 0; // Returns an error code of 0 after displaying sample input
}

int main(int argc, char* argv[]) {
    
    /**********
     * Parse command line arguments for two things:
     * - time_limit
     * - time_delta
     **********/

    if (argc != 3) {
        std::cerr << "\nYou must specify two arguments." << std::endl;
        return usage();
    }

    // Initialize variables to store time-related arguments.
    double time_limit, time_delta, timer;
    timer = 0; // Initializes timer that determines when to end program

    // Check first argument (time limit).
    std::istringstream arg_limit(argv[1]);
    if (!(arg_limit >> time_limit)) {
        std::cerr << "\n'" << argv[1] << "' "
                "is not a valid double value." << std::endl;
        return usage();
    }

    // Check second argument (time delta).
    std::istringstream arg_delta(argv[2]);
    if (!(arg_delta >> time_delta)) {
        std::cerr << "\n'" << argv[2] << "' "
                "is not a valid double value." << std::endl;
        return usage();
    }
    
    /**********
     * Determine the window size and load in the background starfield image.
     **********/
    
    // Window size is determined in main. Assume a square window.
    int win_size = 600;
    sf::RenderWindow window(sf::VideoMode(win_size, win_size), "Solar System");
    window.setFramerateLimit(30);
    sf::Event event;
    
    // Load in the starfield image and scale it to the window size.
    sf::Image starfield_image;
    sf::Texture starfield_texture;
    sf::Sprite starfield_sprite;   
    starfield_image.loadFromFile("files/starfield.jpg");
    starfield_texture.loadFromImage(starfield_image);
    
    // Before loading the starfield into the sprite, we need to get a scaling
    // factor in relation to the window size. Assume a square window.
    sf::Vector2u starfield_dimensions = starfield_texture.getSize();
    double scale_factor = ((double)win_size/starfield_dimensions.x);
    starfield_sprite.setScale(scale_factor,scale_factor);
    starfield_sprite.setTexture(starfield_texture);
    
    /**********
     * Here we scan in the celestial bodies from stdin redirection.
     **********/
    
    // Get number of celestial bodies and universe radius from file.
    int i, j, numOfBodies;
    double univ_radius;
    std::cin >> numOfBodies;
    std::cin >> univ_radius;
    
    // Create Pointers to Bodies based on body count obtained from file
    std::vector<Body*> Bodies;
    for(i=0; i<numOfBodies; i++)
        Bodies.push_back(new Body);
    
    // Along with the six properties on each line, the bodies also need
    // the window size and universe radius for pixel conversion.
    for(i=0; i<numOfBodies; i++){
        std::cin >> (*Bodies[i]);
        (*Bodies[i]).setWindowSize(win_size);
        (*Bodies[i]).setUniverseRadius(univ_radius);
    }
    
    /**********
     * Create music object to allow music to play.
     **********/
    
    sf::Music music;
    if (!music.openFromFile("files/planetkarma.ogg"))
        return -1; // error
    music.play();
    
    /**********
     * Text for displaying timer on screen
     **********/
    
    sf::Font font;
    if (!font.loadFromFile("files/Ubuntu-B.ttf"))
        std::cout << "Error loading font." << std::endl;
    
    std::ostringstream ss; // Needed to convert number to string
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);

    /**********
     * Variables used in calculating net forces on a body object so
     * the acceleration, velocity, and positions can then be
     * calculated internally in the body object.
     **********/

    double x_delta, y_delta;
    double radius, radius_squared;
    double gravity = 6.67e-11;
    double force_radius;
    double force_x, force_y;
    double body_i_mass, body_j_mass;

    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        // Do the physics simulation while the time limit isn't up.
        if (timer <= time_limit) {

            window.clear(sf::Color::Black);
            window.draw(starfield_sprite); // Draws background starfield image

            /**********
             * This big for loop does the physics calculations.
             **********/
           
            for (i = 0; i < numOfBodies; i++) {

                force_radius = 0;
                force_x = 0;
                force_y = 0;
                body_i_mass = (*Bodies[i]).get_Mass();

                // Calculate net forces for each body.
                for (j = 0; j < numOfBodies; j++) {

                    if (j == i)
                        continue; // We ended up at the same body, continue

                    // Change in x and y positions
                    x_delta = (*Bodies[j]).get_X_pos()
                            - (*Bodies[i]).get_X_pos();
                    y_delta = (*Bodies[j]).get_Y_pos()
                            - (*Bodies[i]).get_Y_pos();
                    radius_squared = (x_delta * x_delta)
                            + (y_delta * y_delta);
                    radius = sqrt(radius_squared);
                    body_j_mass = (*Bodies[j]).get_Mass();

                    // Accumulate the forces acting on this "i" body.
                    force_radius = (gravity * (body_i_mass * body_j_mass))
                            / radius_squared;
                    force_x += force_radius * (x_delta / radius);
                    force_y += force_radius * (y_delta / radius);
                }

                // We've gotten the net forces of the other bodies acting on
                // this body. Internally do the other calculations.
                (*Bodies[i]).calculate_X_acceleration(force_x);
                (*Bodies[i]).calculate_Y_acceleration(force_y);
                (*Bodies[i]).step(time_delta);

            } // end big for loop doing physics calculations

            /**********
             * Now we draw the bodies and timer text out to the window.
             **********/

            // Draw the bodies out to the window.
            for (i = 0; i < numOfBodies; i++)
                window.draw((*Bodies[i]));

            // Draw the text.
            ss.str("");
            ss.clear();
            ss << timer;
            text.setString(ss.str());
            window.draw(text);
            timer += time_delta; // Update the timer.

            // Finally display the drawn items above.
            window.display();

        } else {

            // Getting to here means we've reached the time limit.
            // The screen pauses and the timer stops.
            ss.str("");
            ss.clear();
            ss << timer;
            text.setString(ss.str());
            window.draw(text);

        }

    }

    /**********
     * Debugging -- while loop done, stop the music
     **********/

    // Debug: Print out parsed arguments.
    std::cout << "Time Limit: " << time_limit << std::endl;
    std::cout << "Time Delta: " << time_delta << std::endl;

    // Debug: Print out values in the bodies.
    for (i = 0; i < numOfBodies; i++)
        std::cout << (*Bodies[i]);

    music.stop();

    return 0;
    
}

