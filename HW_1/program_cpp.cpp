// Translate this program to C in the file program_c.c
// Compile this program with the command 'g++ program_cpp.cpp -o program_cpp'
// Run it with './program_cpp'

#include <iostream> 
#include <fstream> 
#include <string> 
using namespace std; 

// C does not have classes, use a struct instead 
class Rectangle { 
private: 
    int length, width; 

public: 
    Rectangle(int l, int b) : length(l), width(b) {}

    int area() const { return length * width;}

}; 