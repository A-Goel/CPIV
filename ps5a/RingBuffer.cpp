// Copyright 2015 Roy Van Liew for 91.204 Computing IV
// Fri Mar 27 15:06 2015
// * >>> SOURCES
// * - Willie Boag helped clarify how this queue
// *   should work.
// * - Fred Martin and Olga Lepsky from Computing II for
// *   covering circular arrays.

#include "RingBuffer.hpp"
#include <stdint.h>

// C++ standard libraries
#include <iostream>
#include <string>
#include <vector>

// Exception Handling libraries
#include <exception>
#include <stdexcept>

RingBuffer::RingBuffer(int capacity) {
    if ( capacity < 1 )
        throw std::invalid_argument("Capacity must be > 0");
    _buffer.resize(capacity);
    _capacity = capacity;
    _size = 0;
    _first = 0;
    _last = 0;
}

RingBuffer::~RingBuffer() {
}

int RingBuffer::size() {
    return _size;
}

bool RingBuffer::isEmpty() {
    return ( size() == 0 );
}

bool RingBuffer::isFull() {
    return ( size() == _capacity );
}

void RingBuffer::enqueue(int16_t x) {
    // Cannot add to a full queue.
    if ( isFull() )
        throw std::runtime_error("Cannot enqueue full buffer.");
    _buffer[_last] = x;

    // If at the end, reset back to zero and increment size.
    if (_last == (_capacity-1)) {
        _last = 0;
        _size++;
        return;
    }

    // Otherwise, increment back and size by one.
    _last++;
    _size++;
    return;
}

int16_t RingBuffer::dequeue() {
    // Cannot dequeue from an empty queue.
    if ( isEmpty() )
        throw std::runtime_error("Cannot dequeue empty buffer.");
    int16_t dequeued_int = _buffer[_first];

    // If at the end, reset front to zero and decrement size.
    if (_first == (_capacity-1)) {
        _first = 0;
        _size--;
        return dequeued_int;
    }

    // Otherwise, increment front by one and decrement size.
    _first++;
    _size--;
    return dequeued_int;
}

int16_t RingBuffer::peek() {
    if ( isEmpty() )
        throw std::runtime_error("Cannot peek on empty buffer.");
    return _buffer[_first];
}
