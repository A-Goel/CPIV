/* 
 * File:   ED.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * Implementation of the EditDistance class which calculates a score matrix
 * of integers for two sequences, and also has an alignment function to
 * trace back the alignment without requiring coordinates (albeit is less
 * expressive this way, but cuts down memory usage by a factor of 3).
 * 
 * >>> SOURCES
 * - Michael Zener Riggs Gottlieb helped me implement this dynamic programming
 *   algorithm last year in Python, along with explaining what this algorithm
 *   was doing. I converted the Python code to C++ code here and had to make
 *   several changes, such as removing coordinates in the matrix. See some of
 *   his cool tools here: http://mzrg.com/js/index.shtml
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> // For output formatting
#include <algorithm>
#include "ED.hpp" // Header file with dynamic programming class

EditDistance::EditDistance(std::string sequence1, std::string sequence2)
{       
    int i, rows; // Counter variables for initializing matrix
    gap = 2;
    seq1 = sequence1;
    seq2 = sequence2; 
    matrix.resize(seq1.length()+1); // sequence 1 determines rows.
    rows = matrix.size();
    for (i = 0; i < rows ; i++)
        matrix[i].resize(seq2.length()+1); // sequence 2 determines columns.
    fillGapPenalties();
}

EditDistance::~EditDistance()
{}

void EditDistance::fillGapPenalties()
{
    // Fill bottom row and last column with gap penalty base case.
    int i, j;
    int seq1_length = seq1.length();
    int seq2_length = seq2.length();
    for(i = seq1_length; i >= 0; i--)
        matrix[i][seq2_length] = gap*(seq1_length-i);
    for(j = seq2_length; j >= 0 ; j--)
        matrix[seq1_length][j] = gap*(seq2_length-j);
}

int EditDistance::OptDistance()
{
    // Row by row, column by column, fill the matrix with integers.
    // Start 1 less than sequence length since we filled the gap base cases.
    int i, j;
    int seq1_length = seq1.length();
    int seq2_length = seq2.length();
    for( i = (seq1_length-1); i >= 0; i-- )
        for( j = (seq2_length-1); j >= 0 ; j--)
            matrix[i][j] = min(gap + matrix[i + 1][j],
                gap + matrix[i][j + 1],
                matrix[i + 1][j + 1] + penalty(seq1[i], seq2[j]));
    return matrix[0][0];
}

int EditDistance::penalty(char seq1_char, char seq2_char)
{ return (seq1_char != seq2_char); }

int EditDistance::min(int down_score, int right_score, int diagonal_score)
{
    if(down_score <= right_score && down_score <= diagonal_score)
        return down_score;
    else if(right_score <= diagonal_score)
        return right_score;
    else
        return diagonal_score;
}

std::string EditDistance::alignSequences()
{    
    /* Get alignment from top left to bottom right. We check this order:
     * 1.) Inserting a gap to the second sequence (one row down), +2
     * 2.) Inserting a gap to the first sequence (one column right), +2
     * 3.) Match or replacement (Diagonally down-right), +0 or +1 */
    int i = 0, j = 0;
    int current_score = matrix[i][j];
    int seq1_len = seq1.length(), seq2_len = seq2.length();
    std::string seq1_letter, seq2_letter;
    std::string aligned_string = "";
    while (!(i == seq1_len && j == seq2_len)) {

        if (i == seq1_len) { // At bottom row, go right rest of the way
            while (j < seq2_len) {
                seq2_letter = seq2[j];
                aligned_string += "- " + seq2_letter + " 2\n"; // seq 1 gap
                j++;
            }
            break;
        }

        if (j == seq2_len) { // At rightmost column, go down rest of the way
            while (i < seq1_len) {
                seq1_letter = seq1[i];
                aligned_string += seq1_letter + " - 2\n"; // seq 2 gap
                i++;
            }
            break;
        }

        if (current_score == (matrix[i + 1][j] + 2)) { // row below
            seq1_letter = seq1[i];
            aligned_string += seq1_letter + " - 2\n"; // sequence 2 gap
            ++i, current_score = matrix[i][j];
        } else if (current_score == (matrix[i][j + 1] + 2)) { // right column
            seq2_letter = seq2[j];
            aligned_string += "- " + seq2_letter + " 2\n"; // sequence 1 gap
            ++j, current_score = matrix[i][j];
        } else if (current_score == (matrix[i + 1][j + 1] + 0) ||
                current_score == (matrix[i + 1][j + 1] + 1)) { // diagonal
            seq1_letter = seq1[i]; // no gaps here, just replacement or match
            seq2_letter = seq2[j];
            if (current_score == (matrix[i + 1][j + 1] + 0))
                aligned_string += seq1_letter + " " + seq2_letter + " 0\n";
            else
                aligned_string += seq1_letter + " " + seq2_letter + " 1\n";
            ++i, ++j, current_score = matrix[i][j];
        }
    }
    return aligned_string;
}
