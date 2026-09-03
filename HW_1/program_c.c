// TODO Complete every TODO in this file

// TODO
// Name: Jesus Martinez
// Date: 9/1/2026

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure as the same as classes except they cannot have functions, also all variables are public
struct Rectangle {
    // TODO add the rectangle variables
    int length, width;
};

// Simulate the constructor of the class, use the arrow (->) operator to access the struct variables
void initRectangle(struct Rectangle *rect, int l, int b) {
    // TODO initialize lenght and width
    rect->length = l;
    rect-> width = b;
}

// Functions for a struct need to be defined outside of the 
int area(struct Rectangle *rect) {
    // TODO return the area of the rectangle
    return rect->length * rect->width; 
}

// Use pointers instead of referenced variables
void swapWithPointers(int *a, int *b) {
    // TODO complete the function swap a and b
    
}

int main() {
    // There are no strings in C, we use C strings! Google the meaning.
    // 1. Simple Input and Output: Use printf to print to the console, fgets or scanf to read the user input
    char name[50];
    // TODO get the user name and output it back
    printf("Enter your name: ");
    //fgets(buffer,size,stream)
    fgets(name, sizeof(name), stdin);
    printf("Hello ", name, "!\n");
    // 2. Dynamic Memory Allocation: In C malloc is used to allocated bytes to a pointer
    int n;
    int *arr;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    // TODO allocate space equal to n times the sizeof an integer, google malloc and sizeof
    printf("Enter %d numbers: ", n);
    arr = malloc(n * sizeof(int)); 
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    printf("You entered: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    // TODO delete the data pointed by arr, google free
    free(arr);
    // 3. Structure vs Class
    struct Rectangle rect;
    // TODO initialize rect and print the rectangle area
    initRectangle(rect, 5,10);
    printf(area(rect));
    // 4. File I/O
    FILE *outFile = fopen("example.txt", "w"); // opening file in write mode
    // TODO Output to the file "Hello, this is a test file." and close the file, google fprintf and fclose
    printf("The file is not opened")
    // TODO Open the file "example.txt" in read mode and print its contents, google fgets
    
    // TODO close the file

    // 5. Pointers vs References
    int x = 10, y = 20;
    printf("Before swap: x = %d, y = %d\n", x, y);
    swapWithPointers(&x, &y);
    printf("After swap: x = %d, y = %d\n", x, y);

    // 6. argc and argv works the same in C
    // TODO print the first and last argument in argv like in program_cpp.cpp

    

    return 0;
}
