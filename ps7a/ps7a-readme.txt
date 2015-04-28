/**********************************************************************
 *  readme.txt template                                                   
 *  Kronos PS7a startup
 **********************************************************************/

Name: Roy Van Liew

Hours to complete assignment (optional):


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

Yes, although a little close for my comfort since the date and time
libraries weren't covered until Wednesday, two days before the
assignment was due and finals week is approaching quickly.
 
Before writing out the lines to an output file I had a function which
displayed the lines stored in the vector of strings in the class
object, _file_strings. With this function I was able to check that
the time calculations matched those of the sample report files
provided. I ended up seeing that milliseconds weren't captured in
the Boot Finish lines, so I had to modify my regular expressions
and time calculations accordingly. I had larger numbers when
milliseconds were included in the Boot Finish lines.

Along with the above, passing the Bottlenose tests gives a high
degree of confidence that my application is parsing and tracking
the log information correctly for the boots. However like I
mentioned the milliseconds in the Boot Finish lines were left
out in the sample reports given.


/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each one does.
 **********************************************************************/

I've split this section up into four parts:
1.) Regular Expression for Boot Start
2.) Regular Expression for Boot Finish
3.) Regular Expression for Boot Start Time in time calculations
4.) Regular Expression for Boot Finish Time in time calculations

 
1.) This regular expression does the following:
	- Four digits at the start (Year) followed by dash
	- One to Two digits (Month) followed by dash
	- One to Two digits (Day) followed by one space
	- One to Two digits (Hour) followed by a colon
	- One to Two digits (Minutes) followed by a colon
	- One to Two digits (Seconds) followed by a colon and then by
	  one or more whitespaces
	- '(log.c.166)' literally followed by one or more whitespaces
	- 'server' literally followed by one or more whitespaces
	- 'started.' literally followed by zero or more whitespaces
	- The Year up to the Seconds is captured in parentheses.
	
_e_begin_boot = "([\\d]{4}-[\\d]{1,2}-[\\d]{1,2} "
            "[\\d]{1,2}:[\\d]{1,2}:[\\d]{1,2}):\\s+"
            "\\(log\\.c\\.166\\)\\s+server\\s+started.\\s*";
			
2.) This regular expression does the following:
	- Four digits at the start (Year) followed by dash
	- One to Two digits (Month) followed by dash
	- One to Two digits (Day) followed by one space
	- One to Two digits (Hour) followed by a colon
	- One to Two digits (Minutes) followed by a colon
	- One to Two digits (Seconds) followed by a period
	- One to Three digits (Milliseconds) followed by a
	  period, and one or more letters a through z either
	  lowercase or uppercase, followed by a colon and
	  zero or more whitespaces
	- 'oejs.AbstractConnector:Started' literally followed
	  by one or more whitespaces
	- 'SelectChannelConnector@0.0.0.0:9080' literally
	  followed by zero or more whitespaces
	- The Year up to the Seconds is captured in parentheses.
			
_e_end_boot = "([\\d]{4}-[\\d]{1,2}-[\\d]{1,2} "
            "[\\d]{1,2}:[\\d]{1,2}:[\\d]{1,2})\\.[\\d]{1,3}:[a-zA-Z]+:\\s*"
            "oejs\\.AbstractConnector:Started\\s+"
            "SelectChannelConnector@0.0.0.0:9080\\s*";
			
3.) This regular expression does the following:
	- Four digits at the start (Year) followed by dash
	  is also captured
	- One to Two digits (Month) followed by dash
	  is also captured
	- One to Two digits (Day) followed by one space
	  is also captured
	- One to Two digits (Hour) followed by a colon
	  is also captured
	- One to Two digits (Minutes) followed by a colon
	  is also captured
	- One to Two digits (Seconds) followed by a period
	  is also captured
	- This is used when we're trying to create the lines
	  to write out to file and need to calculate time
	  differences
			
_time_begin_parse = "([\\d]{4})-([\\d]{1,2})-([\\d]{1,2}) "
            "([\\d]{1,2}):([\\d]{1,2}):([\\d]{1,2})";

4.) This regular expression is the same as the one above.
	- Originally this regular expression also captured the
	  numbers that came after the period as milliseconds,
	  but the provided sample reports did not capture these
	  milliseconds.
			
_time_end_parse = "([\\d]{4})-([\\d]{1,2})-([\\d]{1,2}) "
            "([\\d]{1,2}):([\\d]{1,2}):([\\d]{1,2})";


/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/

I needed an application with a few simple calls. After some
brainstorming I basically came up with:
1.) Parse the log file.
2.) After storing information from parsing, write lines for output.
3.) Write out the lines to the output file.

This was really more of a tracking problem than regular expressions.
The regular expressions were rather trivial; I needed a regular
expression for checking if a line in the input file was a boot
start, and a second one for checking if a line was a boot finish.
I created two other regular expressions to parse the time out of
any of these boot start or finish lines to do the time calculations.

There needed to be a way of keeping tracking of our current line
and some sort of flag indicating we've found a boot start or finish
line. Finding a boot start after a previous boot start means that
the previous boot failed, so I had a counter which if it reached
higher than 1 boot start found then that indicated a boot failure.

I used three maps to keep track of three pieces of information:
1.) _boot_start_map
    - Keys were line numbers of boot start
	- Values were strings holding date parsed on that line
	- This map allowed me to store the time information for
	  every boot start found.
2.) _boot_start_to_end_map
    - Keys are the boot start line
	- Values are the corresponding boot finish line
	- If the value was 0, it meant a failed boot start.
	- This map allowed me to store which boot attempts were
	  successful and which ones failed.
3.) _boot_end_map
    - Keys were line numbers of boot finish
	- Values were strings holding date parsed on that line
	- This map allowed me to store the time information for
	  every boot finish found.

I also needed a way of writing out the parsed log information
out to a file. I had a vector of strings which I pushed to
for every boot attempt found and if it failed or not, which
would later be used to write out to an output file.


/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/

I was mainly on my own for this one. Fred Martin did provide sample
code of doing the millisecond calculations on Lecture Capture and
Victor Grinberg showed how to use the regex_match function.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

The main issue was that using the time libraries was discussed two days
before the assignment was due. This assignment was also more of a
tracking problem than anything else, I thought the regular expression
portion was trivial.

I wound up spending a great deal of time trying to implement how I
would keep track of failed boot attempts. I actually prepared the
regular expressions for the services before implementing the tracking
code, although I haven't included them in this submission to keep the
code smaller.
 

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
