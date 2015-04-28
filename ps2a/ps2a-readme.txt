/**********************************************************************
 *  Linear Feedback Shift Register - Part 1
 **********************************************************************/

Name:
Roy Van Liew

/**********************************************************************
 *  Representation used for the register bits
 **********************************************************************/

>>> IN-DEPTH

This is an in-depth description of how I implemented the functions in
this program. Go to the Summary section for a brief overview.

- Constructor
For my implementation of a linear feedback shift register, I initialize
the register in the constructor by take a passed seed string of 1's
and 0's and convert each individual digit into an integer to store
in a vector. This vector represents the register. The tap bit position
is also saved in the constructor. Subtracting the '0' is a simple
way to convert an ascii digit into its corresponding integer digit,
it goes down to bit representation.

- step()
This basically does three things:
	- Determine index needed to reference the tap bit. This is done by
	  getting the size of the register, subtracting 1 due to zero-based
	  counting, and then subtracting the tap value from the end.
	- There are two temporary variables storing the leftmost bit and
	  the tap bit. Then another temporary variable is used to store
	  the result of XOR'ing the two temporary variables (ints 1 or 0).
	- The first integer in the _seed vector is erased to imitate a
	  left shift operation. Then the XOR result is pushed back at the
	  end of the vector. The XOR result is returned from the function.

- generate()
Generates a new integer of a bit length specified by the argument.
	- While a vector of integers was used to represent the register,
	  I used bitset to allow an integer sequence of 1's and 0's to be
	  converted into an integer after step() has been called k times.
	- Since we were working with 32-bit signed integers, I made bitset
	  a 32-length bit sequence. There is a variable padding_end which
	  determines where the leading zeros in the bit sequence stop.
	  Then for the bits that aren't the leading zeroes, step() is
	  called to generate the 1's and 0's in order for the integer we
	  want to create.
	- reversed_bits exists because even when you print out int_bits
	  and you visually see the correct sequence in the output, the
	  integer that results is actually reversed. So if you had all 0's
	  ending with a 1, that should be a 1 -- but without reversed bits,
	  the returned integer would be a 1 followed by all 0's which is
	  T-Min and that is -2147483648.
	- To clarify how bitset works, you can convert the 1's and 0's
	  stored in your bitset variable into an integer by originally
	  converting it to a long, and then typecasting to an integer
	  after. There isn't any direct integer conversion in bitset,
	  which is why that (int) typecast is there.
	  
>>> SUMMARY

A vector was used for the register and bitset was used to convert
a bit sequence to an integer.

- A vector of integers was used to represent the register was simple
  to work with as it's just an ordered sequence of 1's and 0's. To
  remove the leftmost bit just meant to erase the first vector int,
  and to add the XOR result after this "shift" was just a push back.
- bitset was used to create an ordered sequence of 32 bits since the
  register vector could be less than 32 bits. bitset allowed padding
  of zeros on the left side (leading zeroes) to create a full 32-bit
  sequence. This 32-bit sequence could then be converted into
  an integer using the to_ulong() function and typecasting as int.
 
 /**********************************************************************
 *  Boost Unit Tests
 **********************************************************************/
 
 Along with the sample test case provided on the course website, I also
 provided two other test cases to test my implementation:
 1) fiveBitsTapAtTwo
	- Quick sanity check provided from course website
 2) allOnesOrZeroes
	- Displays some behavior related to seeds literally all 1's or 0's
	- If the tap bit is the same as the leftmost shifted bit, step()
	  should always return 0.
 3) edgeCases
	- Checks some of the more extreme cases.
	- Tests boundaries for generate(); we'll only be concerned about
	  1-31 as the passed k in practice, but I still put in some
	  checks if the k passed is out of that range.
	- See that the upper-bound of a 31-bit integer produced from
	  generate() creates T-Max, (2^31) - 1 or 2147483647.
	- Be able to recover from an empty seed string, negative tap
	  bit position, or if the tap bit position is higher than the
	  seed length.

