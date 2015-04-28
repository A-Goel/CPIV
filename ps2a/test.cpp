/* 
 * File:   test.cpp
 * Author: Roy Van Liew
 * Course: 91.204.201 Computing IV - Fred Martin 10:00-10:50 AM MWF
 */

/*
 * >>> SUMMARY
 * This test suite consists of three test cases, including the one
 * that was provided on the course website, to test the
 * functionality of the LFSR implementation.
 */

#include <iostream>
#include <string>
#include "LFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// This test case was provided on the course website.
BOOST_AUTO_TEST_CASE(fiveBitsTapAtTwo) {

  LFSR l("00111", 2);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 0);

  LFSR l2("00111", 2);
  BOOST_REQUIRE(l2.generate(8) == 198);
  
}

// This test case aims to see what happens with some seeds
// that are either all 0's or all 1's.
BOOST_AUTO_TEST_CASE(allOnesOrZeroes) {

  // Starting with all 1's in a short seed
  LFSR l1_stepcalls("111111", 2);
  BOOST_REQUIRE(l1_stepcalls.step() == 0);
  BOOST_REQUIRE(l1_stepcalls.step() == 0);
  BOOST_REQUIRE(l1_stepcalls.step() == 0);
  BOOST_REQUIRE(l1_stepcalls.step() == 1);
  BOOST_REQUIRE(l1_stepcalls.step() == 1);
  BOOST_REQUIRE(l1_stepcalls.step() == 1);
  BOOST_REQUIRE(l1_stepcalls.step() == 1);

  LFSR l1_gen("111111", 2);
  BOOST_REQUIRE(l1_gen.generate(7) == 15); // 0001111
  

  // All 0's in a 31-length seed
  LFSR l2_gen("0000000000000000000000000000000", 16);
  BOOST_REQUIRE(l2_gen.generate(31) == 0);
  

  // Seed of all 1's but the tap bit == leftmost bit which
  // should always result in 0 due to definition of XOR.
  LFSR l3_stepcalls("111", 2);
  BOOST_REQUIRE(l3_stepcalls.step() == 0);
  BOOST_REQUIRE(l3_stepcalls.step() == 0);
  BOOST_REQUIRE(l3_stepcalls.step() == 0);
  BOOST_REQUIRE(l3_stepcalls.step() == 0);

  LFSR l3_gen("111", 2);
  BOOST_REQUIRE(l3_gen.generate(4) == 0);
  
}

// This test case aims to see what happens for some extreme
// cases such as an empty seed or if tap is higher than seed.
BOOST_AUTO_TEST_CASE(edgeCases) {

  // Test boundaries for generate()
  LFSR l1_gen("11010101110110010101010010001", 8);
  BOOST_REQUIRE(l1_gen.generate(0) == 0);
  BOOST_REQUIRE(l1_gen.generate(-5) == -1);
  BOOST_REQUIRE(l1_gen.generate(32) == -1);


  // Have a seed and tap bit position which will result in 0
  // followed by all 1's aka T-Max ((2^31) - 1)
  LFSR l2_gen("00000000000000000000000000000001", 0);
  BOOST_REQUIRE(l2_gen.generate(31) == 2147483647);


  // Test that the constructor is able to deal with
  // empty seeds and a negative tap position
  LFSR l3_stepcalls("",-5);
  BOOST_REQUIRE(l3_stepcalls.step() == 0);


  // Test that if the tap position is negative but
  // the seed is valid, the tap position becomes 0
  LFSR l4_gen("0001",-1);
  BOOST_REQUIRE(l4_gen.generate(2) == 3); // last 2 bits of 0111


  // Test that if the tap position is bigger than
  // the seed, the tap position becomes 0
  LFSR l5_gen("001",6);
  BOOST_REQUIRE(l5_gen.generate(3) == 6); // 110

}
