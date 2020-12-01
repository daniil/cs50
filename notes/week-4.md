## Binary

```
128 64 32 16 8 4 2 1
  0  0  0  0 0 0 0 0
```

Highest is 255 (256 with a 0)

## Hexadecimal

Using power of 16

```
0 1 2 3 4 5 6 7 8 9 A B C D E F
```

```
256 16 1
  0  0 0
```

It can be converted to decimal or other system.

RGB is represented in hexadecimal.

```
00 00 00 // black
FF FF FF // white
```

Often represented as `0x0, 0x1, 0xF, etc`.

Binary can easily be converted into hexadecimal. Each binary group of 4 will correspond to hexadecimal digit.

Memory addresses in our system are represented in hexadecimal in C.

## Pointers

```
int *p;
```

Pointers are just addresses to location in memory where variables live.

- value is a memory address
- type describes the data located at that memory address

The simplest pointer available is the `NULL` pointer. If you don't set pointer's value immediately, you should set pointer value to `NULL`.

Another way to create a pointer is to simply extract the address of an existing variable using address extraction operator - `&`.

The name of the array is actually a pointer to the first element of that array. That's why passing arrays as arguments works as passing by reference, not value.

### Dereferencing

Main purpose of a pointer is to allow us to modify or inspect the location to which it points.

If we have a pointer-to-char called `pc`, then `*pc` is the data that lives at the memory address stored inside the variable `pc`.

`*` can be used as a *dereference operator*. It goes to the reference and accesses the data at that memory location, allowing you to manipulate it.

If you try to dereference a pointer whose value is `NULL` you will get a _Segmentation fault_, but that's a better behaviour than accidental manipulation of unknown pointers.

## Address

```
& - AddressOf Operator
printf("%p\n", &n); // pointer and an address, displayed in hexadecimal

* - Go to an address
printf("%i\n", *&n); // getting an address and going to it
```

Storing the address of the value:

```
int n = 50;
int *p = &n; // pointer data, address of an int
printf("%i\n", *p); // this will print out the address of that variable
```

## Strings

A string is just a pointer to the address of first character of the string. You can figure out where string ends by looking at the null terminating character.

```
char *s = "EMMA";

// From cs50.h
typedef char *string; // create a data type called string that points to a first character of character set

// This would print the same, the address of first character of the string
printf("%p\n", s);
printf("%p\n", &s[0]);
```

## Copying a string

```
char *s = get_string("s: ");
char *t = malloc(strlen(s) + 1); // allocate memory for characters that are typed by a user + 1 for null terminating character

for (int = 0, n = strlen(s); i < n + 1; i++)
{
    t[i] = s[i];
}

// existing function:
strcpy(t, s);
```

## Memory Allocation

Allocate memory (in bytes) and return back the pointer of allocated memory. You need to explicitly free up the memory to avoid memory leaks.

```
// statically obtain an integer
int x;

// dynamically obtain an integer
int *px = malloc(sizeof(int));
```

```
// get an integer from the user
int x = GetInt();

// array of floats on the stack
float stack_array[x];

// array of floats on the heap
float *heap_array = malloc(x * sizeof(float));
```

Use `free(pointer_name);` to free up the memory. Don't free up static memory and don't free up anything more than once.

You can use `valgrind` to test for memory leaks.

`sizeof` returns the size in bytes of a data type

### Data types space

```
Data Type   Size (in bytes)

int         4
char        1
float       4
double      8
long long   8
char*       4 or 8
```

## Memory Storage

- machine code
- globals
- vvv - heap (malloc)
- ^^^ - stack (local variables in functions)

## Swap variables

```
swap(&x, &y); // send addresses of variables as arguments

// take pointers as parameters
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
```

## Low level get_int or get_string

```
#include <stdio.h>

int main(void)
{
    // int
    int x;
    printf("x: ");
    scanf("%i", &x); // get an integer from a user and pass address to a variable
    printf("x: %i\n", x);

    // string
    char s[5];
    printf("x: ");
    scanf(%s, s);
    printf("s: %s\n", s);
}
```

## File Pointers

- `fopen()`
    - Opens a file and returns a file pointer to it.
    - Always check the return value to make sure you don't get back `NULL`.
    - `FILE *ptr1 = fopen("file1.text", "r");`
- `fclose()`
    - Closes the file pointed to by the given file pointer
    - `fclose(ptr1);`
- `fgetc()`
    - Reads and returns the next character from the file pointed to.
    - The operation of the file pointer passed in as a parameter must be "r" for read.
    - `char ch = fgetc(ptr1);`
- `fputc()`
    - Writes or appends the specified character to the pointed-to file.
    - The operation of the file pointer passed in as a parameter must be "w" for write or "a" for append.
    - `fputc('A', ptr1);`
- `fread()`
    - Reads <qty> units of size <size> from the file pointed to and stores them in memory in a buffer (usually an array) pointed to by <buffer>.
    - The operation of the file pointer passed in as a parameter must be "r" for read.
    - `fread(<buffer>, <size>, <qty>, <file pointer>);`
- `fwrite()`
    - Writes <qty> units of size <size> to the file pointed to by reading them from a buffer (usually an array) pointed to by <buffer>.
    - The operation of the file pointer passed in as a parameter must be "w" for write or "a" for append.
    - `fwrite(<buffer>, <size>, <qty>, <file pointer>);`

### Linux cp command

```
char ch;
while ((ch = fgetc(ptr)) != EOF)
    fputc(ch, ptr2);
```

### `fread` example

```
// Stack
int arr[10];
fread(arr, sizeof(int), 10, ptr);

// Heap
double *arr2 = malloc(sizeof(double) * 80);
fread(arr2, sizeof(double), 80, ptr);

// Single char
char c;
fread(&c, sizeof(char), 1, ptr);
```

### `fwrite` example

```
// Stack
int arr[10];
fwrite(arr, sizeof(int), 10, ptr);

// Heap
double *arr2 = malloc(sizeof(double) * 80);
fwrite(arr2, sizeof(double), 80, ptr);

// Single char
char c;
fwrite(&c, sizeof(char), 1, ptr);
```

### Opening files

```
FILE *file = fopen("phonebook.csv", "a"); // r = read, w = write, a = append

char *name = get_string("Name: ");
char *number = get_string("Number: ");

// print (write) strings to file
fprintf(file, "%s, %s\n", name, number);

// close the file
fclose(file);
```

### Checking if file is a jpeg

```
#include <stdio.h>

int main(int argc, char *argv[])
{
    // Ensure user provided a file argument
    if (argc != 2)
    {
        return a;
    }

    // Open file
    FILE *file = fopen(argv[1], "r"); // read
    if (file == NULL)
    {
        return 1;
    }

    // Read 3 bytes from file
    unsigned char bytes[3];
    fread(bytes, 3, 1, file);

    // Check if bytes are 0xff 0xd8 0xff
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
    {
        printf("Maybe\n");
    }
    else
    {
        printf("No\n");
    }
}
```