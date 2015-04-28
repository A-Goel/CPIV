/**********************************************************************
 *  Ring Buffer Data Structure                                                  
 **********************************************************************/

Name: Roy Van Liew
Login: rvanliew
Hours to complete assignment (optional):

/**********************************************************************
 *  Implementation of the Ring Buffer
 **********************************************************************/
 
I basically went by my implementation of the circular array I did in
Computing II for this ring buffer. The buffer is represented with a
vector that gets resized to the capacity passed to the constructor.

To keep things simple, I used four member variables to keep track of
the state of the buffer:
1.) _capacity: The maximum number of elements the buffer can hold.
2.) _size: Counter of how many elements are in the buffer.
3.) _first: The front of the queue. First In, First Out.
4.) _last: The back of the queue. We're adding to the back of the queue.

_size, _first, and _last all get initialized to 0 in the constructor.
_buffer gets resized to the capacity passed in the constructor
argument and _capacity also saves this value. I'll now move on to the
methods.

>>> size()
This method simply just returns _size. The changes to this counter
happen in enqueue() and dequeue(), and that's it.

>>> isEmpty()
Checks if size() == 0 meaning that there are zero items in _buffer.

>>> isFull()
Checks if size() == _capacity meaning _buffer is full.

>>> enqueue()
Takes a 16-bit integer as an argument. This function is split into
three steps.

1.) Use isFull() to check if _buffer is full. If that's the case,
    throw a runtime error. Otherwise, set _buffer[_last] to the
	16-bit integer, where _last represents the index one past the
	most recently added item in the back of _buffer.
2.) If _last is equal to (_capacity-1) that means we've reached the
    end of the circular array, in which case wrap around by setting
	_last back to 0. Increase _size by 1 to represent adding an
	item to the back of the buffer.
3.) If 2.) didn't happen, that means we're not wrapping around.
    Increment both _last and _size by 1.
	
>>> dequeue()
Removes a 16-bit integer from the front of _buffer. This function
is split into three steps.

1.) Use isEmpty() to check if _buffer is empty. If that's the case,
    throw a runtime error since we can't dequeue from an empty
	buffer. Otherwise, save _buffer[_first] into a temporary 16-bit
	integer variable dequeued_int, where _buffer[_first] is the
	item at the front of the buffer.
2.) If _first is equal to (_capacity-1) that means we've reached the
    end of the circular array, in which case wrap around by setting
	_first back to 0. Decrease _size by 1 to represent removing the
	front element of the buffer. Then return dequeued_int.
3.) If 2.) didn't happen, that means we're not wrapping around.
    Increment _first by 1 and decrease _size by 1. Then return
	dequeued_int.
	
>>> peek()
Returns a 16-bit integer from the front of _buffer without removing
it. Use isEmpty() to check if the _buffer is empty. If the buffer is
empty then throw a runtime error. Otherwise, return _buffer[_first]
which is the front item in the buffer.

/**********************************************************************
 *  Testing the Implementation
 **********************************************************************/

Initially I had a main with std::cout statements to see what values my
methods were returning. After getting a general idea, I ran the test
cases provided on the assignment page. There were two provided test
cases. RingBufferconstructor tests that no exception is thrown on a
good constructor call (capacity > 0), and that an exception is thrown
when there is a bad constructor call (capacity < 1).
RingBufferenque_dequeue enqueues 3 items and dequeues those 3 items,
then tests that calling dequeue() after results in a runtime error
exception since the buffer is empty at that point.

After that, I also considered the other cases that weren't included. 
I wrote two other test cases. peek tested that peek() returned a
runtime error exception if it was called on an empty buffer, and
full_buffer tested that enqueue() returned a runtime error exception
if it was called on a full buffer.

/**********************************************************************
 *  Exceptions Implemented
 **********************************************************************/

Two types of exceptions are thrown in the RingBuffer class:
1.) std::invalid_argument
- Constructor
    If the argument is < 1, this exception is thrown.
2.) std::runtime_error
- enqueue()
    If called on a full buffer, this exception is thrown.
- dequeue()
    If called on an empty buffer, this exception is thrown.
- peek()
    If called on an empty buffer, this exception is thrown.

/**********************************************************************
 *  Time and Space Performance
 **********************************************************************/
 
Since we need to allocate 2 bytes for each element in the buffer that's
implemented as a vector, that's 2*N bytes for the int16_t data type
which is O(n) in space.

enqueue(), dequeue(), and peek() are all O(1) operations. Having _first
and _last as indices for the front of the buffer and back of the buffer
respectively, we can easily modify the buffer through simple index
increments or decrements as well as return items in the buffer with
these indices. Also, _size is a counter that prevents us from having to
do calculations with the _first and _last indices to indicate how many
items are in the buffer, and changing _size is just a simple increment
or decrement operation as well.

So in short:
- size(), isEmpty(), isFull(), enqueue(), dequeue(), and peek() are not
dependent on the size of the buffer vector so this Ring Buffer
implementation is constant in time, or O(1) time.
- Since a vector of N elements has to be created in the constructor,
this implementation is linear in space, or O(n) space.
