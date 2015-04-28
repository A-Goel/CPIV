/**********************************************************************
 *  N-Body Simulation ps3b-readme.txt template
 **********************************************************************/

Name: Roy Van Liew
OS: Windows 7, running VirtualBox with LUbuntu
Machine (e.g., Dell Latitude, MacBook Pro): Acer Aspire 5750Z-4835
Text editor: emacs for Makefile, NetBeans for code
Hours to complete assignment (optional):

/**********************************************************************
 *  If you created your own universe for extra credit, describe it
 *  here and why it is interesting.
 **********************************************************************/

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/

These sources are listed in body.cpp -- Willie Boag helped clarify
what net forces as a term meant so I could move on from displaying
only two bodies. I think I should discuss this here as it also goes
into how I took the steps to finish this assignment. This is lengthy
so I'll summarize it into 5 points, and expand each:
1.) Get calculations working for two bodies (e.g. just Earth and Sun).
2.) Trial and Error with figuring out how to calculate net forces.
3.) Designing the for loops that calculated the net forces,
    acceleration, new velocity, and new position for each body.
4.) Explanation of the inner and outer for loop used in physics
    calculations, clarifying step() usage.
5.) Implement timer controlling how long the simulation goes for.

1.) First I used the code from ps3a and tried getting the physics
calculations working for two bodies -- specifically I did the
Earth and the Sun, Bodies[0] and Bodies[3] respectively from
their placements in the file:
- I made sure delta x and delta y were calculated correctly first.
- After getting delta x and delta y between the Earth and the Sun,
  I got the radius distance between them to use in force calculations.
- I got the "radius force" calculated, which was used in calculating
  the x force and y force between the Earth and the Sun.
- Since the Sun and Earth have the same forces acting on each other
  (thanks Willie Boag!) the same x force and y force values were used
  when calculating the acceleration, velocity, and new positions of
  the Earth and the Sun (for both x and y).

2.) After I got the code working in a rather large while loop of
hardcoded calculations, I decided what other mutators and accessors
I could include in the body class. Keeping what Willie Boag said in
mind about the net force being all the forces of the bodies around
the current body added together, this allowed me to experiment with
the force formulas. I remember before I got this working that the
bodies that weren't the sun hit each other and bounced off the
screen. Basically this was the pattern I saw:
- Every force needed to be calculated two bodies at a time. For each
  body, the forces of all the other bodies need to be added first,
  but only one at a time.
- With two bodies you could get delta x and delta y, which gave the
  radius between the two bodies, so that could be used to calculate
  force. The force radius changes for every body's force calculated
  that is acting on the body in question, but the x force and y force
  accumulate these forces so the main different was adding them up.
- After adding up the forces, there were three more things to find:
  1) Acceleration
  2) Velocity
  3) New Position based on velocity
  
3.) The above took a lot of trial and error. However I eventually
came up with the idea that I could for loop through the Bodies vector
and have a second for loop inside which calculated the forces between
that body and all the other bodies -- putting an exception where the
two bodies happened to be the same body due to the nature of the loop.
You'll see in the for loops:
- The outer for loop that's big is calculating the net forces for each
  body. The inner for loop is for adding up the forces of each other
  body acting on the body in question. Notice that the actual
  acceleration, velocity, and new positioning calculations don't occur
  until after this inner for loop is done since we need the net forces
  or our calculations will be wrong. (Thanks Willie Boag!)
- The step() idea made me realize that the code I had was bulky. So I
  reduced the end of the outer for loop into three simple calls:
  - calculate the x acceleration value
  - calculate the y acceleration value
  - call step() with the delta time to obtain new velocity and position
  I had to create mutators for calculating the x and y accelerations of
  the body because the x and y forces calculated were in main, not in
  the class itself, and it seemed better to work with to me.

4.) It's important to note that the net forces were calculated in main
along with the calls to the acceleration mutators, but then the new
velocity and position calculations were done internally through step().
step() sets new values for the x and y velocities and coordinates in
the body object, which is possible with the delta time in seconds
passed. So to recap, the outer for loop in the window while loop is
doing this:
- Have an inner loop add up the net forces.
- Calculate the acceleration after this inner loop for the body in
  question so we can call step() to calculate the new velocities
  and positions for the body.
- This covers the four important calculations:
  - Net Forces (i.e. forces of each surrounding body added up)
  - Acceleration
  - Velocity
  - New Position
  
5.) Finally the code was cleaned up quite a bit at this point. Now
I actually implemented the timer and text displaying on the screen
that displayed the elapsed time. I've included a font to load so
this timer displays; a problem I encountered was that nothing was
displaying to the window because I had no font loaded.
 
/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

 I can't seem to get sound on VirtualBox working. I was able to link
 the SFML Audio library and include the header file in my main, but
 I didn't hear any sound.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

Before my physics calculations were corrected, the bodies moved in all
sorts of crazy directions. It was quite amusing actually. This
assignment also was a nice exercise in starting out simple and working
your way up -- like how I described getting physics calculations done
for just two bodies first, then after that there was trial and error
on the net forces calculations.

Also, the commenting makes these code files look larger, but I think
my comments give both a visual aid and concise explanations about the
purpose of each section. I put emphasis on clarification in my code
over smaller space used.
