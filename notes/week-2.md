## Compiling and Debugging

`<library.h>` - library file with header

`make`:
- preprocessing
    Replaces library includes with source code for those libraries
- compiling
    Compiles C to Assembly (low level instructions sent to CPU and memory)
- assembling
    Converting Assembly to binary
- linking
    Combining all the binary code into output file

`help50`
    `help50 make file`

`debug50`
    After adding a breakpoint: `debug50 ./program`

## Array

`char` is one byte, `int` is 4 bytes, `long` is 8 bytes
`char` - use single quotes
`string` - use double quotes
`%c` is a char placeholder
Each char is just an ASCII character (represented by an int)
To cast char to int - `(int) c1`, in certain contexts implicit casting can happen, ie `printf("%i", c1)`
You can cast int to char as well
String is just an array of characters

### Definition:

```
const int N = 3; // constant, OK to put at the top of the file

float average(int length, int array[]); // average prototype

int scores[N];

scores[0] = 72;
scores[0] = 73;
scores[2] = 33;

// Remember to move this to the top of the file as a prototype
float average(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return (float) sum / (float) length; // cast sum and length as floats
}

printf("Average: %.1f\n", average(n, scores)); // display float to first decimal place only
```

`\0` - null character, null terminating character 8 zero bits == 1 byte. Gets added to the end of the string to know how long the string is.

```
string names[1];
names[0] = "EMMA";

printf("%s\n", names[0]); // implicitly stops at the null character to find end of string
printf("%c%c%c%c%i\n", names[0][0], names[0][1], names[0][2], names[0][3], names[0][4]); // will print a null character as int
```

## Iterate over string

```
for (int i = 0; s[i] != '\0'; i++)
```

or

```
#include <string.h> // includes strlen method

// More time
for (int i = 0; i < strlen(s); i++)

// More space
int n = strlen(s);
for (int i = 0; i < n; i++)

// More succinct
for (int i = 0, n = strlen(s); i < n; i++)
```

Lowercase letters are 32 ASCII characters below the uppercase, you can substract lowercase to get uppercase and it will implicitly cast it
More easily:

```
#include <ctype.h> // includes toupper method

printf("%c", toupper('c')) // takes an int or char
```

Passing arguments to the program:

```
int main (int argc, string argv[])
{
    if (argc == 2)
    {
        printf("hello", %s\n", argv[1]); // argv[0] will be the program name
    }
    else
    {
        printf("hello, world\n");
    }
}

./argv // hello world
```

By default `main` returns 0 if everything goes well, hence the `int main` definition.
To exit from main, you can return a non-zero value, ie `return 1`.

## Functions

`return-type name(argument-list); // arguments are comma separated, each of which has a type and a name`

Function declaration:

`float mult_two_reals(float x, float y);`

Function definition:

```
float mult_two_reals(float x, float y)
{
    return x * y;
}
```

Functions can have no argument or no return:

```
int fn_name(void); // no arguments
void fn_name(int a); // no return
```

## Arrays

Array declaration:

```
type name[size];
double menu_size[5];
```

You can set a value of element of an array that is higher than the bounds, but it's dangerous and can cause segmentation fault errors.

Instantiation syntax:

```
bool truthtable[3] = { false, true, true };
bool truthtable[] = { false, true, true }; // size can be ommitted
```

Multiple dimensions:

```
bool battleship[10][10];
```

You can not assign one array to another using the assignment operator. You need to copy the contents of one array into another.

Arrays are passed by reference - the callee receives the actual array, not a copy of it. Most variables are passed by value.

## Command-Line Arguments

Everything in command-line is treated as a string, so for numbers we'll need to convert the string to an int or float.