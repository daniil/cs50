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
16 1
 0 0
```

It can be converted to decimal or other system.

RGB is represented in hexadecimal.

```
00 00 00 // black
FF FF FF // white
```

Often represented as `0x0, 0x1, 0xF, etc`

## Address

```
& - AddressOf Operator
printf("%p\n", &n); // pointer and an address, displayed in hexadecimal;

* - Go to an address
printf("%i\n", *&n); // getting an address and go to it
```

Storing the address of the value:

```
int n = 50;
int *p = &n; // pointer data, address of an int
printf("%i\n", *p);
```

## Strings

A string is just a pointer to the address of first character of the string. You can figure out where string ends by looking at the null terminating character.

```
char *s = "EMMA";

// From cs50.h
typedef char *string; // create a data type called string that points to a first character of character set

// This would print the same
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

## Memory alloc

Returns back the address of allocated memory. You need to explicitly free up the memory to avoid memory leaks.

Use `free(ponter_name);` to free up the memory.

You can use `valgrind` to test for memory leaks

`sizeof` returns the size in bytes of a data type

## Memory Storage

- machine code
- globals
- heap (malloc)
- stack (local variables in functions)

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

## Opening files

```
FILE *file = fopen("phonebook.csv", "a"); // r = read, w = write, a = append

char *name = get_string("Name: ");
char *number = get_string("Number: ");

// print (write) strings to file
fprintf(file, "%s, %s\n", name, number);

// close the file
fclose(file);
```

## Checking if file is a jpeg

```
@include <stdio.h>

int main(int argc, char *argv[])
{
    // Ensure user provided a file argument
    if (argc != 2)
    {
        return a;
    }

    // Open file
    FILE *file = fope(argv[1], "r");
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