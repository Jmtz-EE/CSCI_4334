/*
About this program: 
  - This program counts words.
  - The specific words that will be counted are passed in as command-line 
    arguments. 
  - The program reads words (one word per line) from the standard input until EOF or 
    an input line starting with a dot '.'
  - The program print out a summary of the number of times each word has appeared. 
  - Various command-line options alter the behavior of the program. 

  E.g., count the number of times 'cat', 'nap', or 'dog' appears.
  > ./main cat nap dog
  Given input:
  cat 
  .
  Expected output: 
    Looking for 3 words
    Result: 
    cat:1
    nap:0
    dog:0
  */


  #include <stdio.h>
  #include <stdlib.h> 
  #include <string.h>
  #include "smp0_tests.h"

/* B2 */
#define LENGTH(s) (sizeof(s) / sizeof(*s))

/* Structures */
/*  Similar to C++ structs, but no member functions or constructors.
    The name of this structure is WordCountEntry.
    Instantiate like: WordCountEntry nameOfStructureInstance;
    C++: Could use std::string for word, but C uses char* 
*/

typedef struct {
  char *word;       /* In C++, could be std::string */
  int counter;
} WordCountEntry;

/* Complete C5 in this function: Allow multiple words to be specified per line.
      strok() can be used to split a line into individual tokens.
      For the seperator characters we use whitespace (spaxe and 
      tab), as well as the newline character '\n'. We could also 
      trim the buffer to get rid of the newline, instead. 
      strok returns NULL when no more tokens are available.
      Google strtok line to learn more about how to use it */

int process_stream(WordCountEntry entries[], int entry_count)
{}










