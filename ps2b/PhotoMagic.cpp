/* 
 * File:   PhotoMagic.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This application takes advantage of the LFSR class to change an image's
 * appearance through generating new bytes and saving this out to disk, and
 * with the same seed and tap bit, the changed image can be converted back
 * to the original image.
 * 
 * >>> SOURCES
 * - This main comes from a template file Fred Martin provided on the course
 *   website (such as the for loops changing the pixel properties).
 * - Fred Martin for providing code for displaying two windows at once.
 * - Fred Martin for explaining the XOR phenomenon (the "photo magic").
 */

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream> // For converting command line arg to integer
#include <string>
#include <iomanip>
#include "LFSR.hpp"

int usage() {
    std::cout << "Usage:\n\tPhotoMagic <input_file> <output_file> "
            "<seed> <tap>\n" << std::endl;
    std::cout << "Example:\n\tPhotoMagic pipe.png encrypted_pipe.png "
            "01101000010100010000 16\n" << std::endl;
    return 0; // Returns an error code of 0 after displaying sample input
}

int main(int argc, char* argv[]) {

    /**********
     * Parse command line arguments for four things:
     * - input_file (string)
     * - output_file (string)
     * - seed (string of 1's and 0's)
     * - tap_bit (integer)
     **********/

    // There should be "5" arguments: program, input file, output file,
    // seed, and tap bit position.
    if (argc != 5) {
        std::cerr << "\nYou must specify four arguments." << std::endl;
        return usage();
    }

    // Initialize variables to store arguments.
    std::string input_file, output_file, seed;
    int tap_bit;

    // Check first argument (input_file).
    std::istringstream arg_input(argv[1]);
    if (!(arg_input >> input_file)) {
        std::cerr << "\n'" << argv[1] << "' "
                "is not a valid string." << std::endl;
        return usage();
    }

    // Check second argument (output_file).
    std::istringstream arg_output(argv[2]);
    if (!(arg_output >> output_file)) {
        std::cerr << "\n'" << argv[2] << "' "
                "is not a valid string." << std::endl;
        return usage();
    }

    // Check third argument (seed).
    std::istringstream arg_seed(argv[3]);
    if (!(arg_seed >> seed)) {
        std::cerr << "\n'" << argv[3] << "' "
                "is not a valid string." << std::endl;
        return usage();
    }

    // Check fourth argument (tap_bit) is a valid integer.
    std::istringstream arg_tap(argv[4]);
    if (!(arg_tap >> tap_bit)) {
        std::cerr << "\n'" << argv[4] << "' "
                "is not a valid integer for the tap bit." << std::endl;
        return usage();
    }
    if (tap_bit < 0) {
        std::cerr << "\n'" << argv[4] << "' tap bit needs to be "
                "between 0 and 31 (inclusive)." << std::endl;
        return usage();
    }
    if (tap_bit > 31) {
        std::cerr << "\n'" << argv[4] << "' tap bit needs to be "
                "between 0 and 31 (inclusive)." << std::endl;
        return usage();
    }

    /**********
     * Read in the input file specified in the command line args
     * and determine the window sizes from the image size.
     **********/

    // original_img is for before the xor application, xor_img is the
    // XOR result. Both picture dimensions will remain the same.
    sf::Image original_img, xor_img;
    if (!original_img.loadFromFile(input_file))
        return -1;
    if (!xor_img.loadFromFile(input_file))
        return -1;

    // Gets the size of the image, with x and y dimensions
    sf::Vector2u size = xor_img.getSize();

    // Render the windows for both the original and XOR'd image
    sf::RenderWindow window_original(sf::VideoMode(size.x, size.y),
				     "Original");
    sf::RenderWindow window_xor(sf::VideoMode(size.x, size.y),
				"PhotoMagic");

    /**********
     * Apply the "photo magic", where each pixel of the input image is XOR'd
     * with a new 8-bit binary sequence created from LFSR's generate(8) calls.
     **********/

    // Create LFSR object for generating new bytes for output image.
    LFSR l(seed, tap_bit);

    // Each pixel has a red, green, and blue property. For each of these
    // three, xor them with a byte generate(8) creates.
    sf::Color pixel;
    for (unsigned int x = 0; x < size.x; x++) {
        for (unsigned int y = 0; y < size.y; y++) {
            pixel = xor_img.getPixel(x, y);
            pixel.r ^= l.generate(8);
            pixel.g ^= l.generate(8);
            pixel.b ^= l.generate(8);
            xor_img.setPixel(x, y, pixel);
        }
    }

    /**********
     * After applying the "photo magic", load these images into textures
     * and then into sprites to be printed out. Save the XOR'd image to
     * disk when the windows are closed.
     **********/

    // Load the images into texture variables
    sf::Texture texture_original, texture_xor;
    texture_original.loadFromImage(original_img);
    texture_xor.loadFromImage(xor_img);

    // Load the textures into sprites to be drawn out
    sf::Sprite sprite_original, sprite_xor;
    sprite_original.setTexture(texture_original);
    sprite_xor.setTexture(texture_xor);

    // Display two windows at once
    while (window_original.isOpen() && window_xor.isOpen()) {
        sf::Event event;
        while (window_original.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_original.close();
        }
        while (window_xor.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_xor.close();
        }
        window_original.clear();
        window_original.draw(sprite_original);
        window_original.display();
        window_xor.clear();
        window_xor.draw(sprite_xor);
        window_xor.display();
    }

    // Finally, save the XOR'd img out to disk.
    if (!xor_img.saveToFile(output_file))
        return -1;

    return 0;

}

