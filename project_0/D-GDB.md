# Crash course in gdb debugging

Debugging a C application is not too difficult if you know the steps. 

First you need to compile the program (you can omit this first step if you compiled with `make`)
using the -g option to add debugging information to the resulting object file, e.g.

> gcc -g main.c -o main.o

(You don't really need to worry about compilation the makefile takes care of this, but it is necessary if you want to work on your own file, make sure to include ALL .c files required for the program in the gcc command)

Second you need to run the debugger with the resulting object file of the previous statement 

> gdb main

Notice I am using main and not main.c, we need to debug the object file that is the executable, since we used `-o main.o` in the example above the object file we need to call is main, you should omit .o

After the previous command the terminal will open gdb and load the information of the program.
NOW YOU CAN START DEBUGGING!

To start the program you can call

> run `<argument list>`

(`<argument list>` is the list of arguments you wish to pass to the program, 
for Project 0 that would be the list of words you will count, e.g. `run cat dog`)

But WAIT! that simply runs the program and does not actually debug, first you need to set
a break point! To set a break point there are actually several ways to do so, the easiest 
one is to break at the start of a function. e.g. Let's set a break point at the start of main

> break main

(you can replace `main` with the name of any other function to break when that function executes)
After you set the break point now you can rerun the program with the "run" command showed above.

You may also create a break at a specific line number by using a filename:line format, e.g.

> break main.c:95

This statement breaks at line 95 in the file main.c; this is equivalent to `break main`, but you may choose any file that was included in compilation and choose any line you want to break at.

After you hit a break point the program will stop execution and give you full control of the program.
When this occurs now you are meant to run some of the following commands to control the flow of
the program. The most useful ones being:

> layout src

"layout" is a command that allows you to change the way the debugger looks, by default the debugger
will only show the next command to execute, if you want to see the whole source code while debugging
you can use "src" to change to the source code layout. There are other layouts available, but this is
the most useful for your purposes. (NOTE: the window sometimes gets messed up when running multiple
commands, you can fix it by going up and down with the arrow keys on your keyboard). You can turn off
the layout with the command "tui disable", reenable it with "tui enable"

> next

> n

"next" or "n" will execute 1 instruction and advance to the next one (if you'd debugged in VS this is
similar to "step over")

> step

> s

"step" or "s" will start to execute and step into the instruction (if possible), this command helps to 
see the execution of functions step by step.

> continue

> c

"continue" or "c" will run the program until it hits another break point or the end of the program.

> print `<variable>`

"print" will allow you to observe the value of any variable currently in the program
(up to the current line, if a variable hasn't been declared yet then it doesn't exist yet)
NOTE: if you are trying to print an array or a pointer you'll need to dereference the location
you want to analyze, e.g. "print arr[0]" or "print *ptr"

alternatively you may use "display" to maintain the variable on screen while debugging.

> display `<variable>`

`<variable>` can be anything that is already declared or will be declared, you may also use pointer notation to navigate to certain memory locations and display its data, e.g. if you want to display the data of entries, running `display entries` will output an address, you can dereference that address and look at the contents of the pointer (in this case a structure), for example `display *entries`

> quit

"quit" will terminate gdb and return to the terminal

PRO TIP: If you press enter without a command the last command executed will rerun.

A list of all the commands available in gdb can be found here: https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf
Checkout more advanced ways of debugging: https://web.eecs.umich.edu/~sugih/pointers/gdb_core.html