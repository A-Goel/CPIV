// Copyright 2015 Roy Van Liew for 91.204 Computing IV

/*
 * >>> SUMMARY
 * Implementation of the Markov Model class which is used in generating
 * randomized text.
 * 
 * >>> SOURCES
 * - On stackoverflow, someone suggested the idea of changing a map to
 *   another map with integers as the keys and strings as the values.
 *   This was how I was able to implement my "number line" interpretation
 *   of determining the next letter to add based on the random number.
 * - Willie Boag suggested the idea of the "number line" as it was cleaner
 *   to think about than using doubles between 0 and 1. Along with that, he
 *   convinced me that using a flat map for all the kgrams and k+1 grams
 *   was easier.
 */

// My libraries, and C libraries
#include <stdlib.h>  // rand

// C++ standard libraries
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Exception Handling libraries
#include <exception>
#include <stdexcept>

// My libraries
#include "MarkovModel.hpp"

MarkovModel::MarkovModel(std::string text, int k) : _order(k) {
    int i;
    int text_size = text.size();
    _text_length = text_size;
    int k_plus_one = k + 1;
    std::string current_kgram;
    std::string single_symbol;
    _alphabet = "";

    // Obtain the alphabet from the text
    for (i = 0; i < text_size; i++) {
        single_symbol = text[i];
        if (static_cast<int>(_alphabet.find(single_symbol)) == -1)
            _alphabet += single_symbol;
    }

    /**********
     * Find all kgrams. If order was 0, then skip this as the k+1 grams are
     * the single letter counts in that case.
     **********/
    if (k > 0) {
        // Get the full non-wrapping portion of k-grams
        for (i = 0; i < text_size - k; i++) {
            current_kgram = text.substr(i, k);
            _kgrams[current_kgram] += 1;
        }

        // Get the wrapped portion of k-grams
        for (i = 1; i <= k; i++) {
            current_kgram = text.substr(text_size - i, text_size);  // Last i
            current_kgram += text.substr(0, k - i);  // First k-i
            _kgrams[current_kgram] += 1;
        }
    }

    /**********
     * Now find all k+1 grams.
     **********/

    // Get the full non-wrapping portion of k+1-grams
    for (i = 0; i < text_size - k_plus_one; i++) {
        current_kgram = text.substr(i, k_plus_one);
        _kgrams[current_kgram] += 1;
    }

    // Get the wrapped portion of k+1-grams
    for (i = 1; i <= k_plus_one; i++) {
        current_kgram = text.substr(text_size - i, text_size);  // Last i
        current_kgram += text.substr(0, k_plus_one - i);  // First k-i
        _kgrams[current_kgram] += 1;
    }
}

MarkovModel::~MarkovModel() {
}

// Prints order, alphabet, and frequencies of k-grams and k+1-grams.
std::ostream& operator<< (std::ostream &out, MarkovModel &mm) {
    std::cout << "> ORDER --> " << mm._order << std::endl;
    std::cout << "> ALPHABET --> " << mm._alphabet << std::endl;
    std::map<std::string, int>::iterator it;
    for (it = mm._kgrams.begin(); it != mm._kgrams.end(); it++)
        std::cout << it->first << " --> " << it->second << std::endl;
    return out;
}

int MarkovModel::order() {
    return _order;
}

int MarkovModel::freq(std::string kgram) {
    // Check if the kgram is null first
    if (kgram == "") {
        if (_order == 0)
            return _text_length;
        else
            throw std::runtime_error("kgram is of wrong order.");
    }

    // Then check to see if the length of the kgram matches the order.
    int k_size = kgram.size();
    if (k_size != _order)
        throw std::runtime_error("kgram is of wrong order.");

    // Otherwise it's fair game. Look up the kgram in the map.
    return _kgrams[kgram];
}

// k+1 gram
int MarkovModel::freq(std::string kgram, char c) {
    // Check to see if the length of the kgram matches the order.
    int k_size = kgram.size();
    if (k_size != _order)
        throw std::runtime_error("kgram is of wrong order.");

    std::string k_plus_one = kgram;
    k_plus_one += c;
    if (_kgrams.count(k_plus_one) == 0)
        return 0;  // Doesn't exist in the map
    else
        return _kgrams[k_plus_one];
}

char MarkovModel::randk(std::string kgram) {
    // Check if the kgram size is the same as the order
    int k_size = kgram.size();
    if (k_size != _order)
        throw std::runtime_error("kgram is of wrong order.");

    // Check if the kgram exists in the map
    if (_kgrams.count(kgram) == 0)
        throw std::runtime_error("Entry doesn't exist in the map.");

    /**********
     * Find all non-zero k+1 grams (i.e. the ones that were found in text)
     **********/
    int total_occurrences = freq(kgram);
    int alphabet_size = _alphabet.size();
    int i, k1gram_occurrences;
    char char_for_k1gram;
    std::string k1gram;
    std::map <std::string, int> k1_freqs;
    for (i = 0; i < alphabet_size; i++) {
        char_for_k1gram = _alphabet[i];
        k1gram_occurrences = freq(kgram, char_for_k1gram);
        k1gram = kgram + char_for_k1gram;
        if (k1gram_occurrences == 0)
            continue;
        k1_freqs[k1gram] = k1gram_occurrences;
    }

    /**********
     * Find cumulative occurrences of each existing k+1 gram for probabilities,
     * then generate a random number between 0 and number of kgram.
     **********/
    int cumulative_freqs = 0;
    std::map <std::string, int> cumulative;
    std::map <std::string, int>::iterator it;
    for (it = k1_freqs.begin(); it != k1_freqs.end(); it++) {
        cumulative_freqs += it->second;
        cumulative[it->first] = cumulative_freqs;
    }
    int rand_result = rand() % total_occurrences; // NOLINT

    /**********
     * Now reorder the cumulative map by having the integer as a key,
     * and the string as a value to reorder for this functionality to
     * work properly
     **********/
    std::map <int, std::string> cumulative_sorted;
    for (it = cumulative.begin(); it != cumulative.end(); it++)
        cumulative_sorted[it->second] = it->first;

    /**********
     * Find out which character to return based on kgram cumulative freqs.
     **********/
    char char_to_return;
    std::map <int, std::string>::iterator it_sortedmap;
    for (it_sortedmap = cumulative_sorted.begin();
            it_sortedmap != cumulative_sorted.end(); it_sortedmap++) {
        if (it_sortedmap->first > rand_result) {
            k1gram = it_sortedmap->second;
            break;
        }
    }
    char_to_return = k1gram[_order];
    return char_to_return;
}

// Generate a string of length T characters.
// Assume that T is at least k.
std::string MarkovModel::gen(std::string kgram, int T) {
    // Throw an exception if kgram is not of length k.
    int k_size = kgram.size();
    if (k_size != _order)
        throw std::runtime_error("kgram is of wrong order.");

    /**********
     * Repeatedly call randk() until we reach T characters. Remember that
     * after randk() is called on a kgram, we have to remove the first letter
     * and then add the result of randk() to the back of the kgram, which
     * will be the new kgram to call randk() on again.
     **********/
    std::string accumulated_chars = kgram;  // Start off with kgram
    std::string current_kgram = kgram;
    int i;
    char randk_result;
    for (i = 0; i < T; i++) {
        randk_result = randk(current_kgram);
        current_kgram.erase(0, 1);  // Remove first character for next k+1 gram
        current_kgram += randk_result;  // Add randk result to end of k+1 gram
        accumulated_chars += randk_result;  // Add randk result to accumulated
    }

    return accumulated_chars;
}
