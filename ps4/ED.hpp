/* 
 * File:   ED.hpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This header file contains the class definition for the Edit Distance class
 * that uses the dynamic programming approach.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class EditDistance{
    
    public:
        EditDistance(std::string sequence1, std::string sequence2);
        ~EditDistance();
        void fillGapPenalties();
        int OptDistance();
        std::string alignSequences();
        int min(int down_score, int right_score, int diagonal_score);
        int penalty(char seq1_char, char seq2_char);
    private:
        std::string seq1; // Original first sequence passed
        std::string seq2; // Original second sequence passed
        std::vector< std::vector<int> > matrix;
        int gap; // Gap penalty
    
};
