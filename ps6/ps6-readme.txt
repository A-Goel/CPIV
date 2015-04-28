/**********************************************************************
 *  readme.txt template                                                   
 *  Markov Model
 **********************************************************************/

Name: Roy Van Liew

Hours to complete assignment (optional): 6 Hours

/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

Yes, although the randk() part took a while. gen() wasn't that bad,
but randk() required me to do some digging and eventually find out
that I could reorder a map by its values by creating a new map. That's
not entirely memory efficient, but it works.

The mmtest test case file provided passes my code, and I was also
able to generate text that resembled the input text -- sometimes
quite humorous, like for the dialogue inputs on the Princeton page.

/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?  
 **********************************************************************/

Nope.

/**********************************************************************
 *  Does your implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/

Yes, I'm able to run mmtest without any errors.

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/

Like I mentioned in the implementation file (MarkovModel.cpp) Willie
Boag suggested the idea of the "number line" as it was cleaner
to think about than using doubles between 0 and 1. Along with that, he
convinced me that using a flat map for all the kgrams and k+1 grams
was easier to work with.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

randk() had me stuck for a while.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

Some of the randomized text generated from this application had me
laughing much harder than I should have.

I also have two test input files in the submission:
- OpeningExercises2014.txt (excerpt from Princeton)
- sierpinski.txt (excerpt from my ps1 readme)

Try running with the following commands:

./TextGenerator 7 700 < sierpinski.txt
./TextGenerator 7 1000 < OpeningExercises2014.txt
