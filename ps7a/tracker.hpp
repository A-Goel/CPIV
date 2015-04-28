// Copyright 2015 Roy Van Liew for 91.204 Computing IV

/*
 * >>> SUMMARY
 * Class structure for Tracker class in ps7a.
 */

// Boost regex header
#include <boost/regex.hpp>

// C++ standard libraries
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

// Boost time headers
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

class Tracker {
 public:
  explicit Tracker(std::string log_name);
  ~Tracker();
  std::string find_begin_boots(std::string line, boost::regex e_begin_boot,
        boost::smatch m, int line_number);
  std::string find_end_boots(std::string line, boost::regex e_end_boot,
        boost::smatch m, int line_number);
  void find_service_start(std::string line, boost::regex service_regex,
        boost::smatch m, int line_number);
  void find_service_finish(std::string line, boost::regex service_regex,
        boost::smatch m, int line_number);
  void parse_log();
  void generate_file_strings();
  int calculate_milliseconds(int start_boot_line, int end_boot_line);
  void write_output_file();

 private:
  int _total_lines;
  int _total_boots;
  int _total_finished_boots;
  std::string _log_name;
  std::vector< std::string > _file_strings;
  boost::regex _time_begin_parse;
  boost::regex _time_end_parse;
  boost::regex _e_begin_boot;
  boost::regex _e_end_boot;
  std::map <int, std::string> _boot_start_map;
  std::map <int, int> _boot_start_to_end_map;
  std::map <int, std::string> _boot_end_map;
};
