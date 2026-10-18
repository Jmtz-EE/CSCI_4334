# Homework 6 - Pthreads

In this homework, you will complete two C programs using POSIX threads (pthreads), the standard thread library available on POSIX-compliant systems.

Pthreads is an explicit threading library: your program creates threads, gives each thread work, and coordinates their lifetimes. A thread is an independent path of execution within the same process. Threads in one process share global variables and memory, but each has its own call stack and local variables. This makes it possible to do independent work concurrently, and it also means that unsynchronized access to shared data can cause bugs.

## Key ideas

- **Concurrency:** Multiple tasks are in progress during the same period. Depending on the machine, threads may take turns on one CPU core or run at the same time on different cores.
- **Shared state:** Data that multiple threads can access, such as the calculator's global `sum`. Two threads updating the same value can interfere with each other.
- **Race condition:** A bug whose outcome depends on the timing or order of thread operations. For example, two threads can both read the same old sum, add their values, and overwrite one another's updates.
- **Mutex:** A mutual-exclusion lock that lets one thread at a time enter a protected section of code. Lock before accessing shared mutable data and unlock when finished. Every lock must be paired with an unlock, including on error paths.
- **Thread lifetime:** `pthread_create` starts a worker; `pthread_join` waits for it to finish. Join workers before reading results they produce or releasing data they use. Give each worker its own argument storage that remains valid until that worker is done.

The mutex should protect the smallest operation that must be indivisible, not unrelated work. It does not make every part of a program thread-safe automatically. Also, a correct result in one run does not prove that a program is free of a race condition: timing can hide the bug.

## 1. Calculator

Use the main thread to read `numbers.txt`, and create one worker thread for each line. Each worker parses its own line and contributes its numbers to the global `sum`. The final answer should be `1000`.

The line buffer used by `fgets` is reused on every read. If every worker receives the address of that same buffer, they may all see a later line instead of the line intended for them. Make a separate copy of each line and keep it valid until its worker has finished. Keep track of how many workers were actually created, then join those workers before printing the final sum. Protect the update to `sum` with `sum_mutex`.

Consider what could happen if two workers read and update `sum` at the same time. The mutex makes each update a critical section: only one worker can perform it at once.

1. Which shared value must be protected by `sum_mutex`? Explain what can go wrong without protection, even if the program sometimes prints `1000`.
2. What operations belong inside the critical section? Why should unrelated work be kept outside it?
3. Why must each line have its own storage, and how long must that storage remain valid?
4. What does `pthread_join` guarantee here? What might happen if the sum is printed before all workers are joined?

## 2. Spellchecker

Use the main thread to load `dictionary.txt` and read a whole line of user input. For each word in the line, create one worker that checks whether the word appears in the dictionary. Report whether each word is spelled correctly. Continue until the user enters a single dot.

Load the dictionary completely before starting any checking threads, and do not modify it while they are reading it. Each worker needs its own word storage, kept valid until that worker is joined. Join the workers before reusing or freeing their word storage. Results may be printed in a different order from the input because workers finish at different times.

The dictionary is shared, but it is read-only while checking. The workers also check separate words, so the program does not need a mutex to protect the dictionary or a shared result value. If you introduce shared mutable state, reconsider whether it needs synchronization. Creating one thread per word is part of this exercise; in a production program, why might a fixed-size worker pool be more efficient or safer for very long input?

1. Why can the checking threads read the same dictionary without a mutex? What assumption about the dictionary must remain true?
2. Do the worker threads write to any shared mutable result? If you change the program to collect results in shared data, what synchronization might be needed?
3. What are the costs and limits of creating one thread per word? How could a bounded number of workers handle a very long line?

## How to compile

Compile either program with:

```sh
gcc -pthread calculator.c -o calculator -g
gcc -pthread spellchecker.c -o spellchecker -g
```

Run the executable from the directory containing the input files.

## How to debug

* Run debugger: `gdb objectName`
* Use Project 0 D file to create breakpoints
* Inspect threads: `info threads`
* Switch threads: `thread n`
* More on POSIX Threads: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
* More on Debugging PThreads: https://sourceware.org/gdb/current/onlinedocs/gdb.html/Threads.html

## Rubric

1. (10 points) Calculator uses 1 thread to read file
2. (20 points) Calculator adds each line with a different thread
3. (10 points) Calculator result is always 1000 (not most of the times).
4. (10 points) Spellchecker uses 1 thread for user input
5. (20 points) Spellchecker uses n threads for spellchecking the n words in line given
6. (10 points) Spellcheker correctly marks mispelled/correctly spelled words. (In any order)
7. (20 points) Questions

Submit a comment in Brightspace when you have completed all the requirements, **double check your commit went through**