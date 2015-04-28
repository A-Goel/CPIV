// Copyright 2015 Roy Van Liew for 91.204 Computing IV
// Fri Mar 27 14:53 2015
// * >>> SOURCES
// * - Fred Martin originally provided this test case file.

// BOOST Libraries
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// C++ standard libraries
#include <stdint.h>
#include <iostream>
#include <string>

// Exception libraries and Ring Buffer header
#include <exception>
#include <stdexcept>
#include "RingBuffer.hpp"

BOOST_AUTO_TEST_CASE(RingBufferconstructor) {
  // normal constructor
  BOOST_REQUIRE_NO_THROW(RingBuffer(100));

  // this should fail
  BOOST_REQUIRE_THROW(RingBuffer(0), std::exception);
  BOOST_REQUIRE_THROW(RingBuffer(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(RingBufferenque_dequeue) {
  RingBuffer rb(100);

  rb.enqueue(2);
  rb.enqueue(1);
  rb.enqueue(0);

  BOOST_REQUIRE(rb.dequeue() == 2);
  BOOST_REQUIRE(rb.dequeue() == 1);
  BOOST_REQUIRE(rb.dequeue() == 0);

  BOOST_REQUIRE_THROW(rb.dequeue(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(peek) {
  RingBuffer rb(5);

  // Starts empty
  BOOST_REQUIRE_THROW(rb.peek(), std::runtime_error);

  // Queue two things, peek should work
  rb.enqueue(654);
  rb.enqueue(32);
  BOOST_REQUIRE(rb.peek() == 654);

  // Dequeue both items, empty buffer again
  rb.dequeue();
  rb.dequeue();
  BOOST_REQUIRE_THROW(rb.peek(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(full_buffer) {
  RingBuffer rb(4);

  // This buffer can only hold 4 items, 5th item is error
  rb.enqueue(1);
  rb.enqueue(2);
  rb.enqueue(3);
  rb.enqueue(4);
  BOOST_REQUIRE_THROW(rb.enqueue(5), std::runtime_error);

  // See that different indices also allow for full checks.
  // Dequeue 3 items, enqueue 3 items, full again.
  rb.dequeue();
  rb.dequeue();
  rb.dequeue();
  rb.enqueue(5);
  rb.enqueue(6);
  rb.enqueue(7);
  BOOST_REQUIRE_THROW(rb.enqueue(8), std::runtime_error);
}
