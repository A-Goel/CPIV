// Copyright 2015 Roy Van Liew for 91.204 Computing IV

/*
 * >>> SUMMARY
 * Implementation of Tracker class in ps7a.
 */

// Boost regex header
#include <boost/regex.hpp>

// C++ libraries
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

// Boost time headers
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

// Header file for Tracker object
#include "tracker.hpp"

using boost::gregorian::date;
using boost::gregorian::from_simple_string;
using boost::gregorian::date_period;
using boost::gregorian::date_duration;

using boost::posix_time::ptime;
using boost::posix_time::time_duration;

Tracker::Tracker(std::string log_name) : _log_name(log_name) {
    // m[1] = year, m[2] = month, m[3] = day,
    // m[4] = hour, m[5] = minute, m[6] = second
    _e_begin_boot = "([\\d]{4}-[\\d]{1,2}-[\\d]{1,2} "
            "[\\d]{1,2}:[\\d]{1,2}:[\\d]{1,2}):\\s+"
            "\\(log\\.c\\.166\\)\\s+server\\s+started.\\s*";
    _e_end_boot = "([\\d]{4}-[\\d]{1,2}-[\\d]{1,2} "
            "[\\d]{1,2}:[\\d]{1,2}:[\\d]{1,2})\\.[\\d]{1,3}:[a-zA-Z]+:\\s*"
            "oejs\\.AbstractConnector:Started\\s+"
            "SelectChannelConnector@0.0.0.0:9080\\s*";
    _time_begin_parse = "([\\d]{4})-([\\d]{1,2})-([\\d]{1,2}) "
            "([\\d]{1,2}):([\\d]{1,2}):([\\d]{1,2})";
    _time_end_parse = "([\\d]{4})-([\\d]{1,2})-([\\d]{1,2}) "
            "([\\d]{1,2}):([\\d]{1,2}):([\\d]{1,2})";
}

Tracker::~Tracker()
{}

std::string Tracker::find_begin_boots(std::string line,
        boost::regex e_begin_boot, boost::smatch m, int line_number) {
    std::string line_to_return = "";
    if (boost::regex_match(line, m, e_begin_boot)) {
        std::stringstream ss;
        ss << line_number;
        std::string line_num_string = ss.str();
        line_to_return = m[1];
    }
    return line_to_return;
}

std::string Tracker::find_end_boots(std::string line, boost::regex e_end_boot,
        boost::smatch m, int line_number) {
    std::string line_to_return = "";
    if (boost::regex_match(line, m, e_end_boot)) {
        std::stringstream ss;
        ss << line_number;
        std::string line_num_string = ss.str();
        line_to_return = m[1];
    }
    return line_to_return;
}

void Tracker::parse_log() {
    std::ifstream log_file(_log_name.c_str());
    boost::smatch m;
    int line_counter = 0;

    // Keeping track of the current boot that's happening
    int current_boot_line = 0;
    std::string current_boot_str = "";
    std::string start_boot_found = "";
    std::string end_boot_found = "";

    // Keeping track of how many boots occurred.
    int start_boot_counter = 0;  // If this is > 1, a boot failed.
    int total_boots = 0;
    int total_successful_boots = 0;

    std::string line;
    while (std::getline(log_file, line)) {
        // Keep track of the line count.
        line_counter++;
        start_boot_found = find_begin_boots(line,
                _e_begin_boot, m, line_counter);
        end_boot_found = find_end_boots(line, _e_end_boot, m, line_counter);

        // If we reached a boot starting line, see if it's after another
        // boot starting line (in which case the previous one failed).
        if ( start_boot_found != "" ) {
            _boot_start_map[line_counter] = start_boot_found;
            total_boots++;
            start_boot_counter++;
            if ( start_boot_counter > 1 )
                _boot_start_to_end_map[current_boot_line] = 0;
            current_boot_line = line_counter;
            start_boot_counter = 1;
        }

        // If we reached a boot end line, match it to the most recently found
        // boot start line.
        if ( end_boot_found != "" ) {
            _boot_end_map[line_counter] = end_boot_found;
            if ( start_boot_counter == 1 ) {
                _boot_start_to_end_map[current_boot_line] = line_counter;
                total_successful_boots++;
                start_boot_counter = 0;
            }
        }
    }

    _total_lines = line_counter;
    _total_boots = total_boots;
    _total_finished_boots = total_successful_boots;
}

void Tracker::generate_file_strings() {
    std::map <int, int>::iterator it_int_int_map;
    int start_boot_num, end_boot_num;
    std::string string_for_file;
    for (it_int_int_map = _boot_start_to_end_map.begin();
            it_int_int_map != _boot_start_to_end_map.end(); it_int_int_map++) {
        start_boot_num = it_int_int_map->first;
        end_boot_num = it_int_int_map->second;
        if ( end_boot_num == 0 ) {
            std::stringstream ss;
            ss << start_boot_num;
            std::string line_num_string = ss.str();
            string_for_file = "=== Device boot ===\n" + line_num_string + "("
                    + _log_name + "): " + _boot_start_map[start_boot_num]
                    + " Boot Start" + "\n**** Incomplete boot ****\n\n";
            _file_strings.push_back(string_for_file);
        } else {
            // First make the string for the boot start line.
            std::stringstream ss;
            ss << start_boot_num;
            std::string line_num_string = ss.str();
            std::string ms_string;
            string_for_file = "=== Device boot ===\n" + line_num_string + "("
                    + _log_name + "): " + _boot_start_map[start_boot_num]
                    + " Boot Start\n";
            _file_strings.push_back(string_for_file);

            // After, make the string for the boot finish line.
            std::stringstream ss_end, ss_ms;
            ss_end << end_boot_num;
            line_num_string = ss_end.str();
            ss_ms << calculate_milliseconds(start_boot_num, end_boot_num);
            ms_string = ss_ms.str();
            string_for_file =  line_num_string + "(" + _log_name + "): "
                    + _boot_end_map[end_boot_num] + " Boot Completed"
                    + "\n\tBoot Time: " + ms_string + "ms\n\n";
            _file_strings.push_back(string_for_file);
        }
    }
}

int Tracker::calculate_milliseconds(int start_boot_line, int end_boot_line) {
    // Save parsed dates into temporary string variables.
    std::string start_boot_full_date, end_boot_full_date;
    start_boot_full_date = _boot_start_map[start_boot_line];
    end_boot_full_date = _boot_end_map[end_boot_line];

    // Retrieve specific date information from the strings.
    boost::smatch m_start, m_end;
    boost::regex_match(start_boot_full_date, m_start, _time_begin_parse);
    boost::regex_match(end_boot_full_date, m_end, _time_end_parse);

    // Create date objects to determine the day of the year.
    std::string day_start_str, day_end_str;
    day_start_str = m_start[1] + "-" + m_start[2] + "-" + m_start[3];
    day_end_str = m_end[1] + "-" + m_end[2] + "-" + m_end[3];
    date date_start(from_simple_string(day_start_str));
    date date_end(from_simple_string(day_end_str));

    // Create ptime objects to allow us to calculate milliseconds.
    // hours, min, sec, nanosec
    ptime time_start(date_start,
                    time_duration(atoi(m_start[4].str().c_str()),
                                  atoi(m_start[5].str().c_str()),
                                  atoi(m_start[6].str().c_str())));
    ptime time_end(date_end,
                    time_duration(atoi(m_end[4].str().c_str()),
                                  atoi(m_end[5].str().c_str()),
                                  atoi(m_end[6].str().c_str())));

    time_duration time_difference = time_end - time_start;
    return time_difference.total_milliseconds();
}

void Tracker::write_output_file() {
    std::string output_name = _log_name + ".rpt";
    std::ofstream outputFile;
    outputFile.open(output_name.c_str());
    int num_of_output_lines = _file_strings.size();
    int i;
    for ( i = 0; i < num_of_output_lines; i++)
        outputFile << _file_strings[i];
    outputFile.close();
}
