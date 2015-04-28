// Copyright 2015 Roy Van Liew for 91.204 Computing IV

/*
 * >>> SUMMARY
 * Main application which creates a Tracker object
 * to capture boot attempts, failed or successful.
 */

// Boost regex header
#include <boost/regex.hpp>

// C++ libraries
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

// Boost time headers
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

// Header file for Tracker object
#include "tracker.hpp"

int usage() {
    std::cout << "Usage:\n\tps7a <log_file>\n" << std::endl;
    std::cout << "Example:\n\tps7a device5_intouch.log\n" << std::endl;
    return 0;  // Returns error code of 0 after displaying sample input
}

int main(int argc, char** argv) {
    /**********
     * Parse command line arguments for the input log file.
     **********/

    // There should be 2 arguments: Program, and input log file.
    if (argc != 2) {
        std::cerr << "\nYou must specify only two arguments." << std::endl;
        return usage();
    }

    // Create the Tracker object and read through the file.
    std::string log_file_name = argv[1];
    Tracker bootLogging = Tracker(log_file_name);
    bootLogging.parse_log();
    bootLogging.generate_file_strings();
    bootLogging.write_output_file();

    return 0;
}

