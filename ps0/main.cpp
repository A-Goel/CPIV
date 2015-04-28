/* 
 * File:   main.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This is the first assignment given, ensuring we get a linux configuration
 * up and running and an introduction to using events in SFML along with
 * creating graphics.
 *
 * >>> SOURCES
 * - http://stackoverflow.com/questions/23530360/how-do-you-make-a-clickable-sprite-in-sfml
 * - http://www.sfml-dev.org/tutorials/2.0/window-inputs.php
 * - http://www.sfml-dev.org/tutorials/2.0/window-events.php
 * - http://www.sfml-dev.org/tutorials/2.0/graphics-sprite.php
 * - http://www.sfml-dev.org/tutorials/2.1/window-window.php
 */

#include <SFML/Graphics.hpp>

int main() {
    // Determine window size and set frame limit
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    window.setFramerateLimit(30);

    // Determine circle properties
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Green);

    // Load a sprite to display, relative path.
    sf::Texture texture;
    if (!texture.loadFromFile("./sprite.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Coordinates for the sprite position
    int x = 0;
    int y = 0;

    // Draw the circle and sprite while the window is open
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // This handles what happens when the user clicks "close"
            if (event.type == sf::Event::Closed)
                window.close();

            // The following handles the arrow keys pressed
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    sprite.move(x - 20, 0); // 20 pixels left
                }
                if (event.key.code == sf::Keyboard::Right) {
                    sprite.move(x + 20, 0); // 20 pixels right
                }
                if (event.key.code == sf::Keyboard::Up) {
                    sprite.move(0, y - 20); // 20 pixels up
                }
                if (event.key.code == sf::Keyboard::Down) {
                    sprite.move(0, y + 20); // 20 pixels up
                }
            }

            // If left mouse button is clicked, rotate sprite
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if ((sf::Mouse::getPosition(window).x > sprite.getGlobalBounds().left) && (sf::Mouse::getPosition(window).x < (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) && (sf::Mouse::getPosition(window).y > sprite.getGlobalBounds().top) && (sf::Mouse::getPosition(window).y < (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)))) {
                    sprite.rotate(15); // 15 degrees clockwise if inside of sprite
                } else {
                    sprite.rotate(-15); // 15 degrees counterclockwise if outside of sprite
                }

            }

        }

        // Move sprite position diagonally to the bottom right
        sprite.move(1, 1);

        // Clear screen
        window.clear();

        // Draw the circle BEHIND the sprite
        window.draw(shape);

        // Draw the sprite OVER the circle
        window.draw(sprite);

        // Update the window
        window.display();
    }

    return 0;
}
