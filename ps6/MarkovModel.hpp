// Copyright 2015 Roy Van Liew for 91.204 Computing IV

/*
 * >>> SUMMARY
 * Class structure for the Markov Model class.
 */

// C++ standard libraries
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Exception Handling libraries
#include <exception>
#include <stdexcept>

class MarkovModel {
 public:
  MarkovModel(std::string text, int k);
  ~MarkovModel();
  int order();
  int freq(std::string kgram);
  int freq(std::string kgram, char c);
  char randk(std::string kgram);
  std::string gen(std::string kgram, int T);

  friend std::ostream& operator<< (std::ostream &out, MarkovModel &mm);

 private:
  int _order;
  int _text_length;
  std::map <std::string, int> _kgrams;  // must #include <map>
  std::string _alphabet;
};
