// TODO Your name:

#include <stdio.h> // printf()
#include <stdlib.h> // atoi(), exit(), ...
#include <string.h> // strtok(), strcmp(), ...
#include <pthread.h> // pthread types and functions 

#define MAX_LINE_LENGTH 255
#define MAX_DICTIONARY_SIZE 202412

char dictionary[MAX_DICTIONARY_SIZE][MAX_LINE_LENGTH];
int dictionary_size = 0;

void *check_word(void *arg) {
    char *word = (char *) arg;
    int i;
    // TODO find in the dictionary if the word exists, if it does print %word% is spelled correctly.


    // TODO if it does not then print %word% is spelled incorrectly.
    
    pthread_exit(NULL);
}

int main() {
    char line[MAX_LINE_LENGTH];
    pthread_t thread; // How many threads do you think we need?
    
    FILE *dictionary_file = fopen("dictionary.txt", "r");
    if (dictionary_file == NULL) {
        printf("Error: cannot open dictionary file\n");
        exit(EXIT_FAILURE);
    }
    while (dictionary_size < MAX_DICTIONARY_SIZE &&
           fgets(dictionary[dictionary_size], sizeof dictionary[0], dictionary_file) != NULL) {
        dictionary[dictionary_size][strcspn(dictionary[dictionary_size], "\r\n")] = '\0';
        dictionary_size++;
    }

    if (dictionary_size == MAX_DICTIONARY_SIZE && fgetc(dictionary_file) != EOF) {
        fprintf(stderr, "Error: dictionary exceeds the maximum of %d entries\n", MAX_DICTIONARY_SIZE);
        fclose(dictionary_file);
        return EXIT_FAILURE;
    }
   


    fclose(dictionary_file);
    printf("Enter a line of text: ");
    // TODO get the user input using fgets until the user enters a single dot
    // for every word create a thread that checks the spelling of that word.
   
    
    pthread_exit(NULL);
}