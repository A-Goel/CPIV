/**********************************************************************
 *  readme template                                                   
 *  DNA Sequence Alignment
 **********************************************************************/

Name: Roy Van Liew
Login: rvanliew
Hours to complete assignment (optional):
iSense Data URL: http://isenseproject.org/projects/871/data_sets/7969


/**********************************************************************
 *  Explain what you did to find the alignment itself.
 **********************************************************************/

To retrieve the alignment I had to start from the top left of the matrix
which is [0][0] to whatever the bottom-right index was. Basically the
bottom right is [seq1_len][seq2_len] since sequence 2 determines the
number of columns in the matrix and sequence 1 determines the number
of rows, and when we reach this point that's when we have retrieved the
full alignment.

I checked for three things in order, same as the matrix-filling:
1.) Inserting a gap to the second sequence, one row down
	- Check if the current score matched ([i+1][j] + 2)
2.) Inserting a gap to the first sequence, one column right
	- Check if the current score matched ([i][j+1] + 2)
3.) Match or replacement (Diagonally down-right)
	- Check if the current score matched ([i+1][j+1] + (0 or 1))

So in short:
1.) Check below row first
2.) Check right column second
3.) Check diagonal last

In every captured check case, the appropriate index was incremented to
move to the next row or column. Two counter variables i and j were used
to store where we were in the matrix. The current score we were at got
updated after incrementing these indices in the captured check cases.

However, there's also a chance of segmentation faults if you are at
the very edge of your matrix when tracing the alignment (very bottom row
or rightmost column) in which case I had checks for this and if they
were true, then I filled gaps for the rest of the sequence depending
if we were on the rightmost column or bottom row.


/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file? 
 * 
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/

Input:
./ED < sequence/endgaps7.txt 

Expected output:
Edit distance = 4
a - 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
- a 2

What happened:
Edit distance = 4
a - 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
- a 2


/**********************************************************************
 *  How much main memory does your computer have? Typical answers
 *  are 4GB and 2GB. If your machine has 1 GB or less, use a cluster
 *  machine for this readme (see the checklist for instructions).
 **********************************************************************/

From executing the "free" command on OS308-03 in the Olsen 3rd floor lab
computer, I see 6.38 GB of memory available.

rvanliew@os308-03 ~/workspace/computing4/ps4 $ free
             total       used       free     shared    buffers     cached
Mem:       7837128    1456752    6380376      41928     149224     716552
-/+ buffers/cache:     590976    7246152
Swap:      7902204          0    7902204


/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of 
 *  N. Give an answer of the form a * N^b for some constants a 
 *  and b, where b is an integer. Note chars are 2 bytes long, and 
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 1GB (billion bytes) of memory?
 **********************************************************************/

a = 4
b = 2
largest N = 15811

Filling out the integers in the matrix requires 4 bytes for every
integer and getting all the possible paths requires filling out a 2D
matrix. So that is 4*(15811^2) = 999,950,884 bytes ~ 1 GB. However,
this is just for filling in the matrix. The string created in the
alignment function also requires a decent deal of memory, but not
nearly as much as the matrix.


/**********************************************************************
 *  Were you able to run Valgrind's massif tool to verify that your
 *  implementation uses the expected amount of memory?
 *
 *  Answer yes, no, I didn't try, I tried and failed, or I used a 
 *  different tool.
 *
 *  If yes, paste in the ms_print top chart of memory use over time,
 *  and also indicate which file your code was solving.
 * 
 *  Explain if necessary.
/**********************************************************************

Yes, and here is the ms_print top chart for ecoli28284.txt:

    GB
2.982^                                                                       :
     |  :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
     |  @                                                                    #
     |  @                                                                    #
     | :@                                                                    #
     | @@                                                                    #
     | @@                                                                    #
     | @@                                                                    #
     | @@                                                                    #
     | @@                                                                    #
     | @@                                                                    #
     | @@                                                                    #
     |:@@                                                                    #
     |:@@                                                                    #
     |:@@                                                                    #
     |:@@                                                                    #
     |@@@                                                                    #
     |@@@                                                                    #
     |@@@                                                                    #
     |@@@                                                                    #
   0 +----------------------------------------------------------------------->Gi
     0                                                                   28.96

The ending table is more useful when it comes to seeing how much
memory was used. The above graph does show a gigantic spike in the
increased memory usage, but a nicer table is here. As we can see, 3202 MB
(approximately 3.2 GB) was used in this application for ecoli28284.txt which
basically goes to the 4*(28284^2) calculation for memory needed.

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 72 31,085,767,493    3,201,662,808    3,201,096,978       565,830            0
 73 31,098,741,046    3,201,793,840    3,201,228,021       565,819            0


/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *
 *  If you get segmentation fault when allocating memory for the last
 *  two test cases (N=20000 and N=28284), note this, and skip filling
 *  out the last rows of the table.
 **********************************************************************/

>>> WITH VALGRIND
data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt       118            0.176094
ecoli5000.txt       160            0.598817
ecoli7000.txt       194            1.12733
ecoli10000.txt      223            2.23985
ecoli20000.txt      3135           8.73424
ecoli28284.txt      8394           17.2919

>>> WITHOUT VALGRIND
data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt       118            0.030543
ecoli5000.txt       160            0.110869
ecoli7000.txt       194            0.206058
ecoli10000.txt      223            0.408491
ecoli20000.txt      3135           1.77606
ecoli28284.txt      8394           3.79963


If you wish, please enter your data on a shared visualization for the 
whole class to view. Go to this URL:

http://isenseproject.org/projects/ xxx (TBD!)

and enter contributor key 204.

Then click on Contribute Data > Manual Entry, and enter your data.

For each row of data, enter the string length (e.g., 2500) and your run
time in seconds (e.g., 0.08).

Click "Add Row" to add enough rows for all of your entries.

Name your data set with your CS username and details about your computer
(processor, RAM, and OS).

Note this was an older readme downloaded. The link to my data set is
both at the top of this file and here:
http://isenseproject.org/projects/871/data_sets/7969


/*************************************************************************
 *  Here are sample outputs from a run on a different machine for 
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730


/**********************************************************************
 *  For this question assume M=N (which is true for the sample files 
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a 
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use 
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 * 
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/

>>> WITHOUT VALGRIND
data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt       118            0.030543
ecoli5000.txt       160            0.110869
ecoli7000.txt       194            0.206058
ecoli10000.txt      223            0.408491
ecoli20000.txt      3135           1.77606
ecoli28284.txt      8394           3.79963

Structure = a * N^b of N
Function = 2 * ( (N/21225)^2 )
a = 2
b = 2
largest N = 4,411,533

>>> WITH VALGRIND
data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt       118            0.176094
ecoli5000.txt       160            0.598817
ecoli7000.txt       194            1.12733
ecoli10000.txt      223            2.23985
ecoli20000.txt      3135           8.73424
ecoli28284.txt      8394           17.2919

Structure = a * N^b of N
Function = 2 * ( (2N/20000)^2 )
a = 2
b = 2
largest N = 2,078,460


/**********************************************************************
 *  List whatever help (if any) you received from the course TAs,
 *  instructor, classmates, or anyone else.
 **********************************************************************/

I learned about the dynamic programming algorithm a year ago when I
took Bioinformatics as a technical elective last spring. Michael
Zener Riggs Gottlieb helped me understand the algorithm and I also
mentioned him in the ED.cpp file.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

There were two main things:
1) My Windows 7 laptop with VirtualBox was sluggish, so I had to use
the Olsen 3rd floor computers.
2) I had code that worked on either VirtualBox or the Olsen computers,
but not both. Eventually I did adjust my code to make it work for
both, but this is something I've never encountered before.

My Windows 7 laptop with VirtualBox could only do up to ecoli20000.txt
and even then that took 50 seconds.

I also experienced lots of odd behavior throughout this assignment
related to how my code ran on different computers, but that got
resolved. Adjusting my code to check the diagonal first made my
align function messy and I disliked that tremendously, but then
bottlenose was modified to also accept other checking orders so then
I was able to go back to my previous code that checked the order
I described earlier: down, right, diagonal.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

