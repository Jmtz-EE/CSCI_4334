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

    int area() const { return length * width; }
};

// Function to demonstrate Pointers vs References
void swapWithReferences(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main(int argc, char **argv) {
    // 1. Simple Input and Output
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Hello, " << name << "!" << endl;

    // 2. Dynamic Memory Allocation
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;
    int *arr = new int[n];
    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << "You entered: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    delete[] arr;

    // 3. Structure vs Class
    Rectangle rect(5, 10);
    cout << "Area of rectangle: " << rect.area() << endl;

    // 4. File I/O
    ofstream outFile("example.txt");
    outFile << "Hello, this is a test file.\n";
    outFile.close();

    ifstream inFile("example.txt");
    string content;
    while (getline(inFile, content)) {
        cout << "File content: " << content << endl;
    }
    inFile.close();

    // 5. Pointers vs References
    int x = 10, y = 20;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swapWithReferences(x, y);
    cout << "After swap: x = " << x << ", y = " << y << endl;

    // 6. argc and argv are used to pass arguments from the command line when you first call the program
    cout << "Number of arguments provided: " << argc << endl;
    cout << "The first argument is the name of this program: " << argv[0] << endl;
    if (argc > 1) {
        cout << "The last argument provided was: " << argv[argc-1] << endl; 
    }
    else {
        cout << "Provide at least another argument when you are running the program, i.e. './program_name arg1'" << endl;
    }

    return 0;
}