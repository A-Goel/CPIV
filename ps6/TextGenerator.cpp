// Copyright 2015 Roy Van Liew for 91.204 Computing IV

/*
 * >>> SUMMARY
 * This application takes in an order for the markov model and the length
 * of the text generated as parameters, and takes a text file piped from
 * stdin as the text to randomize.
 */

// C++ standard libraries
#include <iostream>
#include <fstream>  // File stream
#include <sstream>  // For converting command line arg to integer
#include <string>
#include <exception>
#include <stdexcept>

// My libraries
#include "MarkovModel.hpp"

int usage() {
    std::cout << "Usage:\n\tTextGenerator <order> <output_length> "
            "< <text_file>\n" << std::endl;
    std::cout << "Example:\n\tTextGenerator 7 500 "
            "< OpeningExercises2014.txt\n" << std::endl;
    return 0;  // Returns error code of 0 after displaying sample input
}

int main(int argc, char** argv) {
     /**********
     * Parse command line arguments for two things:
     * - order
     * - output length of generated string
     **********/

    // There should be "3" arguments: program, order, and output length.
    if (argc != 3) {
        std::cerr << "\nYou must specify two arguments." << std::endl;
        return usage();
    }

    int order, output_length;

    // Check first argument (order).
    std::istringstream arg_order(argv[1]);
    if (!(arg_order >> order)) {
        std::cerr << "\n'" << argv[1] << "' "
                "is not a valid integer value for the order." << std::endl;
        return usage();
    }

    // Check second argument (output_length).
    std::istringstream arg_outputlen(argv[2]);
    if (!(arg_outputlen >> output_length)) {
        std::cerr << "\n'" << argv[2] << "' "
                "is not a valid integer value for output length." << std::endl;
        return usage();
    }

    // Read in file contents piped from stdin.
    std::string accumulated_text = "";
    std::string current_text;
    while ((std::cin >> current_text)) {
        accumulated_text += " " + current_text;
        current_text = "";
    }

    // Generate the randomized text, starting with the beginning of the file's
    // text contents.
    std::string start = accumulated_text.substr(0, order);
    MarkovModel mm = MarkovModel(accumulated_text, order);
    std::cout << "\n" << mm.gen(start, output_length) << "\n" << std::endl;

    return 0;
}
