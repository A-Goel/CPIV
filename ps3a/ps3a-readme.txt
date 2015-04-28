/**********************************************************************
 *  N-Body Simulation ps3a-readme.txt template
 **********************************************************************/

Name: Roy Van Liew
OS: Windows 7, running VirtualBox with LUbuntu
Machine (e.g., Dell Latitude, MacBook Pro): Acer Aspire 5750Z-4835
Text editor: emacs for Makefile, NetBeans for code
Hours to complete assignment (optional):

/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
	
This section has code snippets and appears large, however I have tried
my best to be concise here. The topics covered are:
- Celestial Body Object as Drawable
- Loading the Universe from stdin
- Overloaded >> Operator for Reading a Line in Universe File
- Supporting Arbitrary Number of Body Objects (per universe file)
- Scaling Works for Arbitrary Universe Size and SFML Window Size
	
>>> Celestial Body Object as Drawable

Since draw is a const function in SFML's Drawable class, I had to
create a new Sprite object to allow setting a coordinate position
in the SFML window in pixels for the body image:

    sf::Sprite image_in_pixels = _image_sprite;
    image_in_pixels.setPosition( distance_to_pixel() );
    target.draw(image_in_pixels);
	
distance_to_pixel() also had to be const to prevent compiler errors.
Basically, the idea of distance_to_pixel() is to convert the large
distance number, in meters, to a rate of conversion that specified
how many meters were in a pixel. The following is code with the
comments removed:

    double meter_per_pixel = _universe_radius/(_window_size/2.0);
    double x_pixel, y_pixel; // Stores conversion of distance to pixel.
    
    if(_x_coordinate >= 0.0)
        x_pixel = (_window_size/2.0) + (_x_coordinate/meter_per_pixel);
    else
        x_pixel = (_window_size/2.0) - (_x_coordinate/meter_per_pixel);
    
    if(_y_coordinate >= 0.0)
        y_pixel = (_window_size/2.0) - (_y_coordinate/meter_per_pixel);
    else
        y_pixel = (_window_size/2.0) + (_y_coordinate/meter_per_pixel);
    
    return sf::Vector2f(x_pixel,y_pixel);
	
You can see that meter_per_pixel is the variable that stores the
conversion rate between meters and pixels based on the window's size.
Assuming a square window, the center of the universe is the window's
size divided by two, which is where the (_window_size/2.0) comes
from. For instance, if the square window is 600x600, then the center
is 300x300, and 300 is half of 600. This is the offset to start with,
and then depending on if the coordinate in meters was positive or
negative, it will add or subtract from this offset.

In main, the vector of Body objects is run through with a for loop
by index. Since we're working with pointers to Body objects, every
instance has to be dereferenced for drawing.

	for(i=0; i<numOfBodies; i++)
        window.draw((*Bodies[i]));
		
>>> Loading the Universe from stdin

Originally I parsed the file as a command line argument. However,
it wasn't that hard to change it so the file could be used as
input with stdin. This is, of course, assuming the file is
properly formatted from the start. A counter variable is declared,
along with two other variables to store the universe's radius
and the number of celestial bodies. Note the universe radius
denotes the distance from the center of the window to the side.
cin is called twice to read in the two lines, in order,
containing the number of celestial bodies and universe radius.
Luckily it goes past whitespace so that's not an issue here.

    int i, numOfBodies;
    double radius;
    std::cin >> numOfBodies;
    std::cin >> radius;
	
Now that we know the number of celestial bodies, we can create
that many Body objects (specifically, pointers to them).

	std::vector<Body*> Bodies;
    for(i=0; i<numOfBodies; i++)
        Bodies.push_back(new Body);
		
Since cin saves where we are in the file, we know we are at
the body property lines now. These lines are right after the
universe radius line, and each has six properties. The >>
operator is overloaded for the Body object to call cin
six times every time it is used. Along with that, the
window size and universe radius are stored into the Body
objects so they are able to use this information to convert
to pixels on the SFML window. Remember we have pointers
to Body objects, so they have to be dereferenced when used.

   for(i=0; i<numOfBodies; i++){
        std::cin >> (*Bodies[i]);
        (*Bodies[i]).setWindowSize(win_size);
        (*Bodies[i]).setUniverseRadius(radius);
    }
	
The variable storing the number of bodies also allows us to
read a certain number of lines just for the planets we're working
with.

>>> Overloaded >> Operator for Reading a Line in Universe File

The specific call to scanning in one of the six-property
lines in the universe file is inside a for loop in main:

	std::cin >> (*Bodies[i]);
	
In the friend function for the overloaded >> operator there is
the following, which calls std::cin six times to scan in everything
in the row for that specific celestial body. After these six
std::cin calls, setImage is a mutator that takes the image name
read in and prepares the sprite object for drawing later.

	in >> body._x_coordinate;
    in >> body._y_coordinate;
    in >> body._x_velocity;
    in >> body._y_velocity;
    in >> body._mass;
    in >> body._image_file;
    body.setImage(body._image_file);
	
>>> Supporting Arbitrary Number of Body Objects (per universe file)
	
See "Loading the Universe from stdin" section. std::cin is
originally called twice to retrieve the number of celestial bodies
and the universe radius. The number of celestial bodies is saved
into a variable, which dictates how many Body objects are created
and how many rows are read in for those Body objects.
	
>>> Scaling Works for Arbitrary Universe Size and SFML Window Size

See "Celestial Body Object as Drawable" section. There is a method
distance_to_pixel() that is generalized and can find the conversion
rates between meters to pixels for the SFML window in any size. In
main the window size is defined, and this window size is also
saved in the Body object to allow for this conversion to pixels.

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/

 I've also included these sources in the body.cpp file, but will also
 discuss here.
 
 Fred Martin explained the universe radius and its relevance in the
 SFML window, and also explained stdin and the input redirection
 operator so the input planets.txt file didn't have to be parsed as
 an argument. It also made the code smaller!
 
 Olga Lepsky helped me think about the conversion from distance in
 meters to pixel locations on the SFML window.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

 Most issues were resolved in class discussion, such as the stdin
 specification that required the input redirection operator.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

The commenting in the code should make it easy to follow. A sample run
of the application is:

	./NBody < planets.txt
