Pointers in C
-------------

1) Consider the following C program.

```c
#include <string.h>
int main(int argc, char *argv[])
{
  char *temp;
  strcpy(temp, argv[0]);
  return 0;
}
```

Why is the above code incorrect (i.e., likely to crash)?

```
Answer:
```

2) Consider the following C program.

```c
#include <string.h>
int main(int argc, char *argv[])
{
  char temp[9];
  strcpy(temp, argv[0]);
  return 0;
}
```

A buffer overflow occurs when the program name is 9 characters long
(e.g., "12345.exe"). Why?

```
Answer:
```


3) Consider the following C program.

```c
#include <string.h>
int main(int argc, char *argv[])
{
  char *buffer = "Hello";
  strcpy(buffer, "World");
  return 0;
}
```

Why does this program crash?

```
Answer:
```

4) Consider the following C snippet.

```c
void myfunc()
{
  char b[100];
  char *buffer = &b[0];
  strcpy(buffer, "World");
}
```

Is this correct?  What's a simpler expression for &b[0]?

```
Answer:
```

5) Consider the following C program.

```c
#include <stdio.h>
int main(int argc, char* argv[])
{
  printf("%s %s %s\n", *argv, (*(argv+1)) + 2, *(argv+2));
  return 0;
}
```

If this code is executed using the following line, what will be the output?

> ./program1 -n5 abc

```
Answer:
```

6) Consider the following C program.

```c
#include <stdio.h>
#include <string.h>
char *myfunc(char **argv)
{
  char buffer[100];
  strcpy(buffer, "hello");
  return buffer;
}
int main(int argc, char *argv[])
{
  char *s = myfunc(argv);
  printf("%s\n", s);
}
```

What's wrong with this?

```
Answer:
```

7) For students coming from C++: The following C++ code works fine.
   Explain why the equivalent C code is problematic:

```cpp
// C++ version - works fine
std::string getName() {
    std::string name = "Alice";
    return name;  // std::string handles copying
}

int main() {
    std::string result = getName();
    std::cout << result << std::endl;
}
```

Now consider this C version:

```c
// C version - WRONG!
char *getName() {
    char buffer[50];
    strcpy(buffer, "Alice");
    return buffer;  /* DANGEROUS! */
}

int main() {
    char *result = getName();
    printf("%s\n", result);  /* Undefined behavior! */
}
```

Why doesn't this work in C, and what are two ways to fix it?

```
Answer:
```
````
