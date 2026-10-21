// TODO Your name: Jesus Martinez

#include <stdio.h> // printf()
#include <stdlib.h> // atoi(), exit(), ...
#include <string.h> // strtok(), strcmp(), ...
#include <pthread.h> // pthread types and functions 

#define MAX_LINE_LENGTH 100
#define NUM_THREADS 4

int sum = 0;
pthread_mutex_t sum_mutex; // Mutex variables help keep the threads synchronized

void *add_line_numbers(void *arg) {
    char *line = (char *) arg;
    
    // Break down the line and add every number in the line to line_sum
    // strtok_r is the thread-safe version of strtok: it stores its position
    // in a local saveptr instead of hidden global state, so two threads
    // cannot corrupt each other's parse mid-token.
    char *saveptr;
    char *token = strtok_r(line, " \t\n", &saveptr);
    while (token != NULL) {
        pthread_mutex_lock(&sum_mutex); // locks the mutex variable so that only one thread can access it at a time
        // TODO add the number in token to sum, remember to convert it from string to int using atoi()
        sum = sum + atoi(token); //My note: Using the atoi() for the conversion

        pthread_mutex_unlock(&sum_mutex); // unlocks the mutex variable so that other threads can access it

        token = strtok_r(NULL, " \t\n", &saveptr); //My note: On the first call to strtok() the string to be parsed should be 
        // specified in str in each subsequent call that shoudl parse the same string, str should be NULL 
    }
    
    pthread_exit(NULL);
}

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&sum_mutex, NULL);
    file = fopen("numbers.txt", "r");
    if (file == NULL) {
        printf("Error: cannot open file\n");
        exit(EXIT_FAILURE);
    }
    int line_count = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // TODO Create your threads with the given line (remember sharing address locations is not good with threads, create a copy of the line read)

        line_count++;
    }
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        // TODO Wait until all threads finish reading the lines

    }

    // Print final result, it must always be 1000, 
    printf("Sum of all numbers in the file is %d\n", sum);


    fclose(file); // close file in use
    pthread_mutex_destroy(&sum_mutex); // destroys the mutex variable
    pthread_exit(NULL); // destroys main thread
}