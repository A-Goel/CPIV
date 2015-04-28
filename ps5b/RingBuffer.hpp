// Copyright 2015 Roy Van Liew for 91.204 Computing IV

// C libraries
#include <stdint.h>

// C++ libraries
#include <iostream>
#include <vector>

class RingBuffer {
 public:
    explicit RingBuffer(int capacity);
    ~RingBuffer();
    int get_capacity();
    void set_buffer(std::vector<int16_t> buff);
    int size();
    void empty();
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
