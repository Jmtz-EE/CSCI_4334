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