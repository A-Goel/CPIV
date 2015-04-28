/**********************************************************************
 *  readme.txt template                                                   
 *  Recursive Graphics
 **********************************************************************/

Name:
Roy Van Liew

OS:
LUbuntu running on top of Windows 7 (via VirtualBox)

Text editor:
NetBeans, Emacs, Notepad++

Hours to complete assignment (optional):
This one is interesting. I'll list the recorded times I had on this.

1/24/2015	150 mins (before assignment was given)
1/25/2015	60 mins (before assignment was given)
1/26/2015	375 mins
1/27/2015	325 mins
1/28/2015	250 mins
1/29/2015	180 min
			1340 min (22 hr)
			
Below I explain what really happened for those numbers. There was
a lot of exploring I did in this assignment and being new to SFML I
tried out many things that didn't work out the way I wanted.

/**********************************************************************
 *  Describe your artistic creation, and how you went about writing   
 *  a program to produce it. If you found information about a
 *  fractal from somewhere (like our book, the booksite, or
 *  another offline or online source) mention it here. 
 *  (Note that you must not have used *code* from sources other than the
 *  book/booksite, and even such code should be cited in the program.)
 **********************************************************************/

The Staircase recursive design initially draws one square, and then
puts a small square on the top-left and the bottom right. This forms
a staircase pattern, and you can see subsets of staircases if you look
diagonally down-right across the window. Initially I made Sierpinski's
Triangle by calculating midpoints of the three coordinates, and then
making recursive calls to deal with the left, top, and right triangles
(respectively). The midpoint formula I used for that was also applied
in the Staircase design for the squares being placed to the right.
The idea of integrals, calculating an area below a function from
adding a bunch of rectangles as the width of them approaches zero,
made me want to try imitating an integral for a triangle. If you make the
recursion depth high enough (such as 10), you see there's basically
a solid line going down-right diagonally across the screen, splitting
the screen into two triangles.

/**********************************************************************
 *  An analysis of how much memory each of the programs uses,
 *  depending on the recursion depth:
 **********************************************************************/

>>> Sierpinski

Depth	Upside-Down Triangles
1		1 (0*3 + 1)
2		4 (1*3 + 1)
3		13 (4*3 + 1)
4		40 (13*3 + 1)
5		121 (40*3 + 1)
6		364 (121*3 + 1)
7		1093 (364*3 + 1)
8		3280 (1093*3 + 1)
9		9841 (3280*3 + 1)
10		29524 (9841*3 + 1)

You can see a pattern of increasing a factor of 3 for each depth.
- For every depth you go down, you triple the number of triangles drawn.
- You also have 3 coordinates for each triangle, so the pattern turns into
  a 9 aka (3^2) factor increase for the number of coordinates being stored.

>>> Staircase

Depth	Squares
1		1 (0+1) aka + 2^0
2		3 (1+2) aka + 2^1
3		7 (3+4) aka + 2^2
4		15 (7+8) aka + 2^3
5		31 (15+16) aka + 2^4
6		63 (31+32) aka + 2^5
7		127 (63+64) aka + 2^6

- The number of squares drawn is (2^n) - 1. For every depth you go
down, you double the number of squares drawn.
- We're storing basically storing 2^n square shapes in the vector, and
  4 points each square turns that into 2^(n+2) coordinates stored,
  since 4 = (2^2).

>>> Note

The taxing memory requirements of these algorithms is also why I
implemented some boundaries in the application. You cannot go above a
recursion depth of 10 or it simply just exits out of the application.
Along with that the window size must be at least 100 pixels wide.

The draw operation involves iterating through the vector storing
the shapes (and then drawing the coordinates in each). When the depth
got past 12, the window froze and didn't display an image.

/**********************************************************************
 *  Did you receive help from classmates, past COS 126 students, or
 *  anyone else?  Please list their names.  ("A Sunday lab TA" or 
 *  "Office hours on Thursday" is ok if you don't know their name.)
 **********************************************************************/

Fred Martin discussed a possible way of implementing Sierpinski's
Triangle through midpoints. There were also a couple results from
stackoverflow concerning command line parsing and the idea of
storing shapes in a vector to print later, which I mentioned in the
code. Victor Grinberg also helped with a linker problem I had from
the makefile and it was resolved quickly.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

I felt the process I went through in this assignment was more
appropriate to discuss here.

Basically I already had an idea of how Sierpinski's Triangle could
be implemented, but what really took a long time was actually getting
a working class definition for printing out all the triangles. The
Line Demo, for instance, only concerned one line. I did try making
just a simple triangle and square at first with the ConvexShape
class with mapping coordinates, and Fred Martin pointed out why
my simple triangle wasn't working which was a good step forward (he
also provided a makefile). Then eventually as I pointed out earlier
I implemented a vector to store these shapes, which could then
be iterated over in the draw method. Originally I was getting all
sorts of bizarre compiler errors concerning RenderTarget and such.

This assignment was mostly trial-and-error for me since I couldn't
really find issues regarding classes and shapes being stored in them.
Along with that, the Staircase idea was just one of several choices
I tried out; most of my other ideas didn't turn out the way I wanted,
and this one made me content. After I got the classes working I
basically tried to clean up the code to be more nice to read; you may
notice heavy comment usage.

To finish, the snow storm interfered with a lecture which could
have been useful in discussing the assignment more and going to office
hours to specifically describe issues. I did start this assignment
early and basically tried exploring the SFML portions myself, so I
may have made things harder than they needed to be.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

This assignment gave me insight as to how some interesting patterns
can be made through recursion. I could even see a subset of stairs
in my staircase design, and other classmates' fascinating designs as
well. This was a great recursive exercise -- most of the frustration
was just getting class definitions to work with SFML.