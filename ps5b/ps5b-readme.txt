/**********************************************************************
 *  readme.txt template                                                   
 *  Plucking a Guitar String
 **********************************************************************/

Name: Roy Van Liew
CS Login: rvanliew


Hours to complete assignment (optional):


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

Yes, I completed it and it seems to work successfully. I passed the
GStest.cpp file provided and the sounds that are being produced when
I press keys seem reasonable.

Concerning the RingBuffer, that already passed in ps5a. I got through
several errors when compiling my code that were related to segmentation
faults and some other bizarre errors. I basically went with what the
Princeton assignment specified for what these functions were supposed
to do in terms of the formulas, and Willie Boag also helped clarify how
the samples, GuitarString, Sound, and SoundBuffer objects connected
together so what I did in my implementation looks reasonable.

/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?  As a pair, or individually?
 *  If you completed the AutoGuitar, what does it play?
 **********************************************************************/

Nope.

/**********************************************************************
 *  Does your GuitarString implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/

Yes, it passed GStests.cpp and that was a good test file to start with.

Originally I didn't know why my implementation was failing, but it
turned out that in the tic and sample section I was consistently
getting lower integers than the test case specification (995 vs. 996
is an example) which told me that I needed to store the decay factor
result into a double so the answer didn't consistently get rounded
down.

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/

Like I mentioned, Willie Boag also helped clarify how the samples,
GuitarString, Sound, and SoundBuffer objects connected together.
He also suggested the idea of using a map which seemed much more
natural as an approach for looking up the key presses, kind of like
how you can look up an immutable object in a dictionary in Python.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

The rand thing was rather annoying. I was able to getting something
working with rand_r since cpplint complained about rand, but it
required some online digging and Victor even said rand_r was being
obsoleted.

After all that, rand_r broke bottlenose. So I had to go back to rand.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
