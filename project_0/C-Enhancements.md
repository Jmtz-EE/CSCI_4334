Part Three:  Enhancements
-------------------------

Add the following features to the program:

1) Alter the program such that only the correct output is sent to the standard
output stream (stdout), while error and help messages are sent to the standard
error stream (stderr).  (Hint: use fprintf.)

See the expected output listed in the comment at the top of main.c for an
example of what should go to stdout.

2) Implement an optional command-line switch '-fFILENAME' that sends program
output to a file named FILENAME (i.e., filename specified as a command line
argument). For example if the program is executed as

> ./main cat dog -fmyfile.txt

then the program should create a file named "myfile.txt" and contain everything 
after the statement "Looking for 2 words"
(Hint 1: Understand the FILE data type and the function 'fopen'.
Hint 2: DO NOT USE the function 'freopen' it is forbidden it messes up the tests and it is not necessary.
Hint 3: You can update the function signatures if needed.)

3) Add support for matching arbitrary numbers of words, not just 5.
(Hint: use malloc, allocate slightly more than you might need).

4) Safeguard the program from buffer overflow attacks. (Hint: 'gets'
is BAD.  Use fgets instead, which specifies the maximum number of
characters to be read in.)

5) Allow multiple words to be specified per line.
(Hint 1: Understand 'strtok'.
Hint 2: Be careful about the newline character '\n' at the end of the line.)