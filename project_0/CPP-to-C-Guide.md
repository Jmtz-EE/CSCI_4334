# C++ to C Transition Guide

For students transitioning from C++ to C, this guide highlights key differences and common pitfalls.

## Input/Output

### C++
```cpp
std::cout << "Hello, world!" << std::endl;
std::cerr << "Error message" << std::endl;
int x;
std::cin >> x;
```

### C
```c
printf("Hello, world!\n");
fprintf(stderr, "Error message\n");
int x;
scanf("%d", &x);
```

**Key differences:**
- No stream operators (`<<`, `>>`)
- Must use format specifiers: `%s` (string), `%d` (int), `%f` (float), `%c` (char)
- Separate functions for different output destinations (stdout vs stderr)
- Must manually add newlines with `\n`

---

## String Handling

### C++
```cpp
std::string name = "Alice";
std::string greeting = "Hello, " + name;
if (name == "Alice") { }
int len = name.length();
```

### C
```c
char name[50];
strcpy(name, "Alice");
strcat(name, "Hello, ");  // Concatenate
if (strcmp(name, "Alice") == 0) { }  // Compare strings
int len = strlen(name);
```

**Key differences:**
- No `std::string` class - use character arrays (`char[]`)
- `==` operator compares POINTERS, not string content - use `strcmp()` instead!
- String functions from `<string.h>`: `strcmp()`, `strcpy()`, `strlen()`, `strcat()`
- NO automatic bounds checking - must allocate enough space
- `strcmp()` returns: 0 (equal), <0 (first < second), >0 (first > second)

---

## Memory Management

### C++
```cpp
int *arr = new int[10];
delete[] arr;

std::string *str = new std::string("hello");
delete str;
```

### C
```c
int *arr = malloc(10 * sizeof(int));
free(arr);

char *str = malloc(6);  // "hello" + null terminator
strcpy(str, "hello");
free(str);
```

**Key differences:**
- Use `malloc()` instead of `new`
- Must manually free memory with `free()` when done
- Easy to leak memory if you forget to `free()`
- Must calculate correct size in bytes using `sizeof()`
- Cast return of `malloc()` for safety: `int *p = (int*)malloc(10 * sizeof(int));`
- No constructors/destructors - initialization is manual
- RAII pattern not available - manual resource management required

---

## Data Structures

### C++
```cpp
class Person {
public:
    std::string name;
    int age;
    void printInfo() {
        std::cout << name << " is " << age << std::endl;
    }
};

Person p;
p.age = 25;
```

### C
```c
typedef struct {
    char *name;
    int age;
} Person;

void printPerson(Person *p) {
    fprintf(stdout, "%s is %d\n", p->name, p->age);
}

Person p;
p.age = 25;
```

**Key differences:**
- No classes - use `struct` keyword
- No member functions - functions are separate
- No encapsulation - all struct members are public
- Use `.` operator for stack variables, `->` for pointers
- No constructors - must manually initialize fields

---

## Comparison Operations

### Comparing Strings
```c
// WRONG in C (compares pointer addresses)
if (str1 == str2) { }

// CORRECT in C (compares string content)
if (strcmp(str1, str2) == 0) { }
if (!strcmp(str1, str2)) { }  // Also correct, returns 0 when equal
```

### Comparison Functions
```c
strcmp(s1, s2)    // Returns: 0 (equal), <0 (s1 < s2), >0 (s1 > s2)
strcpy(dest, src) // Copy string (watch for buffer overflow!)
strlen(s)         // Return length of string (NOT including null terminator)
strcat(s1, s2)    // Append s2 to s1 (watch for buffer overflow!)
```

---

## Language Features

| Feature | C++ | C |
|---------|-----|---|
| **Operator overloading** | ✓ Supported | ✗ Not available |
| **Function overloading** | ✓ Supported | ✗ Must use different names |
| **References (&)** | ✓ Supported | ✗ Only pointers (*) |
| **Default arguments** | ✓ Supported | ✗ Not available |
| **Class inheritance** | ✓ Supported | ✗ Not available |
| **Templates** | ✓ Supported | ✗ Not available |
| **Exceptions** | ✓ Try/catch | ✗ Use return codes |

---

## Common Mistakes

### 1. String Comparison
```c
// WRONG
if (name == "Alice") { }  // Compares pointer addresses!

// RIGHT
if (strcmp(name, "Alice") == 0) { }
```

### 2. Uninitialized Pointers
```c
// WRONG
char *str;
strcpy(str, "hello");  // Crashes! str points to garbage

// RIGHT - Option 1: Use array
char str[50];
strcpy(str, "hello");

// RIGHT - Option 2: Allocate memory
char *str = malloc(6);
strcpy(str, "hello");
free(str);
```

### 3. Returning Local Variables
```c
// WRONG
char *getName() {
    char buffer[50];
    strcpy(buffer, "Alice");
    return buffer;  // Buffer goes out of scope!
}

// RIGHT - Option 1: Allocate on heap
char *getName() {
    char *buffer = malloc(50);
    strcpy(buffer, "Alice");
    return buffer;  // Caller must free()
}

// RIGHT - Option 2: Pass output buffer
void getName(char *buffer, int size) {
    strncpy(buffer, "Alice", size - 1);
    buffer[size - 1] = '\0';
}
```

### 4. Buffer Overflow
```c
// WRONG - gets() is DANGEROUS
char buffer[10];
gets(buffer);  // What if user enters 20 characters?

// RIGHT - fgets() limits input
char buffer[10];
fgets(buffer, sizeof(buffer), stdin);
```

### 5. sizeof() with Pointers
```c
char *arr = malloc(10 * sizeof(char));
int size = sizeof(arr);  // WRONG! Returns size of pointer, not array

// CORRECT - pass size separately
int size = 10;
processArray(arr, size);
```

---

## Helpful Resources

- **Man pages:** `man <function_name>` (e.g., `man strcmp`, `man malloc`)
- **Quick reference:** Check C library function signatures
- **Debugging tool:** GDB (Gnu DeBugger) - covered in D-GDB.md
- **Testing:** Use provided test runner to validate your code

---

## Summary

The key mindset shift from C++ to C:
1. **Explicit is better than implicit** - You control everything
2. **Safety is your responsibility** - Buffer overflows, memory leaks, etc.
3. **Understand pointers** - They're fundamental to C
4. **Read man pages** - C standard library has excellent documentation
5. **Test frequently** - Use provided tests to catch bugs early

---


# C Quick Reference for C++ Programmers

Quick side-by-side comparison of common operations.

## I/O Operations

| Task | C++ | C |
|------|-----|---|
| Print line | `std::cout << "text" << std::endl;` | `printf("text\n");` |
| Print to stderr | `std::cerr << "error";` | `fprintf(stderr, "error");` |
| Print integer | `std::cout << x;` | `printf("%d", x);` |
| Print float | `std::cout << f;` | `printf("%f", f);` |
| Print string | `std::cout << str;` | `printf("%s", str);` |
| Print character | `std::cout << c;` | `printf("%c", c);` |
| Read integer | `std::cin >> x;` | `scanf("%d", &x);` |
| Read string | `std::cin >> str;` | `scanf("%s", str);` |
| Read line | `std::getline(std::cin, str);` | `fgets(str, size, stdin);` |

---

## String Operations

| Task | C++ | C |
|------|-----|---|
| Compare | `if (s1 == s2)` | `if (strcmp(s1, s2) == 0)` |
| Compare (not equal) | `if (s1 != s2)` | `if (strcmp(s1, s2) != 0)` |
| Copy | `s1 = s2;` | `strcpy(s1, s2);` |
| Copy safely | `s1 = s2;` | `strncpy(s1, s2, size-1);` |
| Concatenate | `s1 += s2;` | `strcat(s1, s2);` |
| Concatenate safely | `s1 += s2;` | `strncat(s1, s2, size-1);` |
| Length | `s.length()` | `strlen(s)` |
| Find substring | `s.find("x")` | `strstr(s, "x")` |
| Compare first n chars | `s1.substr(0, n) == s2.substr(0, n)` | `strncmp(s1, s2, n) == 0` |

---

## Memory Management

| Task | C++ | C |
|------|-----|---|
| Allocate single object | `int *p = new int;` | `int *p = malloc(sizeof(int));` |
| Allocate array | `int *arr = new int[10];` | `int *arr = malloc(10 * sizeof(int));` |
| Initialize memory | `memset(p, 0, size);` | `memset(p, 0, size);` |
| Copy memory | `memcpy(dest, src, size);` | `memcpy(dest, src, size);` |
| Free single | `delete p;` | `free(p);` |
| Free array | `delete[] arr;` | `free(arr);` |
| Reallocate | N/A | `p = realloc(p, new_size);` |

---

## Data Structures

| Task | C++ | C |
|------|-----|---|
| Define struct | `struct Point { int x; int y; };` | `typedef struct { int x; int y; } Point;` |
| Create instance | `Point p;` | `Point p;` |
| Create pointer | `Point *p = new Point();` | `Point *p = malloc(sizeof(Point));` |
| Access member | `p.x = 5;` | `p.x = 5;` |
| Access via pointer | `p->x = 5;` | `p->x = 5;` |
| Member function | `p.distance();` | `distance(&p);` (separate function) |

---

## Control Flow

| Task | C++ | C |
|------|-----|---|
| If statement | `if (cond) { }` | `if (cond) { }` |
| If-else | `if (cond) { } else { }` | `if (cond) { } else { }` |
| Switch | `switch (x) { case 1: ... break; }` | `switch (x) { case 1: ... break; }` |
| For loop | `for (int i = 0; i < 10; i++)` | `for (int i = 0; i < 10; i++)` (C99+) |
| For loop (C89) | N/A | `int i; for (i = 0; i < 10; i++)` |
| While loop | `while (cond) { }` | `while (cond) { }` |
| Do-while | `do { } while (cond);` | `do { } while (cond);` |

---

## String Searching & Manipulation

| Task | C++ | C |
|------|-----|---|
| Split string | `stringstream ss(str); ss >> token;` | `strtok(str, delim)` |
| Convert to int | `int x = std::stoi(str);` | `int x = atoi(str);` |
| Convert to long | `long x = std::stol(str);` | `long x = atol(str);` |
| Convert to float | `float x = std::stof(str);` | `float x = atof(str);` |
| Uppercase | `std::transform(s.begin(), s.end(), ...)` | `toupper(c)` on each char |
| Lowercase | `std::transform(s.begin(), s.end(), ...)` | `tolower(c)` on each char |

---

## File I/O

| Task | C++ | C |
|------|-----|---|
| Open file | `std::ifstream file(name);` | `FILE *f = fopen(name, "r");` |
| Check open | `if (file.is_open())` | `if (f != NULL)` |
| Read line | `std::getline(file, line);` | `fgets(line, size, f);` |
| Write line | `file << line;` | `fprintf(f, "%s", line);` |
| Close file | `file.close();` | `fclose(f);` |
| Check EOF | `file.eof()` | `feof(f)` |

---

## Command-Line Arguments

| Task | C++ | C |
|------|-----|---|
| Access | `argv[i]` | `argv[i]` (same) |
| Count | `argc` | `argc` (same) |
| Convert to int | `std::stoi(argv[1])` | `atoi(argv[1])` |
| Convert to long | `std::stol(argv[1])` | `atol(argv[1])` |

---

## Common Gotchas

| Gotcha | C++ | C |
|--------|-----|---|
| String equality | `==` works (string class) | `==` FAILS (compares pointers) |
| Array size | `std::array<int, 10>` knows size | `int arr[10]` - size NOT stored |
| Buffer overflow | STL containers auto-resize | Manual checking required |
| Memory management | RAII, smart pointers | Manual malloc/free |
| Null pointer | `nullptr` | `NULL` or `0` |
| Function overloading | ✓ Supported | ✗ Not available |

---

## Format Specifiers (printf/scanf)

| Type | Format | Example |
|------|--------|---------|
| Integer | `%d` | `printf("%d", 42);` |
| Long | `%ld` | `printf("%ld", 42L);` |
| Float | `%f` | `printf("%f", 3.14);` |
| Double | `%lf` | `printf("%lf", 3.14);` |
| Character | `%c` | `printf("%c", 'A');` |
| String | `%s` | `printf("%s", "hello");` |
| Hex | `%x` | `printf("%x", 255);` |
| Octal | `%o` | `printf("%o", 8);` |
| Pointer | `%p` | `printf("%p", ptr);` |
| Size | `%zu` | `printf("%zu", size);` |

---

## Tips for Success

1. **Always compare strings with strcmp()**, never `==`
2. **Check malloc() return value** - can fail and return NULL
3. **Use sizeof()** when allocating: `malloc(10 * sizeof(int))`
4. **Always free() what you malloc()** - set to NULL afterward
5. **Use strncpy/strncat** instead of strcpy/strcat to prevent overflow
6. **Use fgets() instead of gets()** - gets() is unsafe
7. **Compile with `-Wall`** to catch many common mistakes
8. **Read man pages**: `man strcpy`, `man malloc`, `man printf`
9. **Use GDB to debug** - see D-GDB.md for reference
10. **Test with provided test runner** before submitting
