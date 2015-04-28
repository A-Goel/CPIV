/* 
 * File:   LFSR.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * Implementation of the LFSR class. Note this does not have much error
 * handling. It was clarified in the Google Group that we'd only pass k
 * of up to 31 to not have to worry about signs for 32-bit integers.
 * 
 * >>> SOURCES
 * - "http://stackoverflow.com/questions/14104208/convert-integer-to-binary-
 *   and-store-it-in-an-integer-array-of-specified-sizec"
 * - The above link introduced me to bitset as a way to store bits in order.
 * - Fred Martin provided a sample LSFR class structure as well as a layout
 *   for these functions.
 */

#include <iostream>
#include <string>
#include <vector>
#include <bitset> // For storing a sequence of bits in order
#include "LFSR.hpp"

// Constructor that initializes the register and tap position for step().
LFSR::LFSR(const std::string seed, const int tap) :
_tap (tap)
{

    // Make sure we're able to deal with an empty seed string
    if (seed != "") {

        int i;
        int seedlen = seed.length();
        _seed.resize(seedlen); // Make this vector as long as the string seed.

        // Note: Simple way of converting each char digit to int digit
        // is to subtract '0' value for exact bit value of the integer digit.
        for (i = 0; i < seedlen; i++)
            _seed[i] = seed[i] - '0';

        if (tap > seedlen)
            _tap = 0; // This means the tap was larger than the seed itself
        else if (tap < 0)
            _tap = 0; // This means tap was negative

    } else {
        // Getting to here means we had an empty seed.
        _seed.resize(1);
        _seed[0] = 0; // This means seed string was empty, just make it 0
        _tap = 0;
    }

}

LFSR::~LFSR()
{
}

int LFSR::step()
{

    // Get the indices of the left-most bit and the tap bit first.
    // Then save these bits in temporary variables and XOR them.
    int tap_index = ((_seed.size()) - 1) - _tap; // Index for the tap bit used
    int leftmost_bit = _seed[0];
    int tap_bit = _seed[tap_index];
    int xor_result = leftmost_bit ^ tap_bit;
    
    // Remove the leftmost bit to imitate a left shift, and then add the
    // XOR result to the end of the vector.
    _seed.erase( _seed.begin() );
    _seed.push_back(xor_result);
    return xor_result; // Return the result of the XOR in this step.
    
}

// Generates a k-bit integer, also meaning step gets called k times to make it.
int LFSR::generate(int k)
{
    
    // We will not accept any k higher than 31 or less than 0.
    if( k > 31 )
        return -1;
    else if( k < 0 )
        return -1;
    else if( k == 0 )
        return 0;
    
    // NOTE: Defining a bitset automatically fills it with zeroes.
    // What's needed is to find where this padding ends to start bit sequence.
    int i, j;
    int padding_end = 32 - k; // Where the leading zeroes stop
    std::bitset<32> int_bits, reversed_bits; // 32-bit sequences for int
    
    // Now call step() to fill in the non-padded portion of the bit sequence.
    for(i=padding_end; i<32; i++)
        int_bits[i] = step();
    
    // Reverse the bit sequence, for some reason I have to do this.
    // I think this goes into little-endian/big-endian topic.
    for(i=0,j=31; i<32; i++,j--)
        reversed_bits[j] = int_bits[i];
    
    // NOTE: bitset only allows conversion to unsigned long,
    // but we can typecast to integer after the conversion.
    int real_integer = (int)(reversed_bits.to_ulong());
    return real_integer;
    
}

std::ostream& operator<< (std::ostream &out, LFSR &lfsr) {
    
    int i;
    int seedlen = lfsr._seed.size();
    for (i = 0; i < seedlen; i++)
        out << lfsr._seed[i];
    return out;
    
}
