/**********************************************************************                                              
 *  Linear Feedback Shift Register - Part 2
 **********************************************************************/

Name:
Roy Van Liew

/**********************************************************************
 *  Functionality
 **********************************************************************/

This program is able to encode and decode an image with the same seed
and tap bit position. The comments in PhotoMagic.cpp show the flow
of the code pretty well, but it's also important to recap the XOR
phenomenon that allows this "photo magic" to be possible.

From the course website:
"XOR operation is reversible (XOR to 0 does nothing; XOR to 1 inverts)"

If we take the following in-class example:

	101		5 (Original image)
	011		3 (represents integer from generate(8))
	---		XOR, 5^3
	110		6 (XOR Result with original, bits for encoded image)
	011		3 (represents integer from generate(8))
	---		XOR, 6^3
	101		5 (XOR Result with encoded image, comes back to original)

/**********************************************************************
 *  Other Notes
 **********************************************************************/
 
 A sample execution command for the program is as follows, assuming you
 have done make all:
 
 ./PhotoMagic original.png encrypted.png 101000010100010 10

