// Copyright 2015 Roy Van Liew for 91.204 Computing IV
// Fri Mar 27 15:06 2015
// * >>> SOURCES
// * - Fred Martin for giving a handout about this
// *   class structure for the Ring Buffer class.

#include <stdint.h>
#include <iostream>
#include <vector>

class RingBuffer {
 public:
        explicit RingBuffer(int capacity);
        ~RingBuffer();
        int size();
        bool isEmpty();
        bool isFull();
        void enqueue(int16_t x);
        int16_t dequeue();
        int16_t peek();

 private:
        std::vector<int16_t> _buffer;
        int _capacity;
        int _size;
        int _first;
        int _last;
};

