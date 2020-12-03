## Big O notation

"On the order of": `O(n)`, `O(log n)`

### Common running times:

`O` is the worst cases, upper bound

- *O(n^2)* - eg. bubble sort, selection sort, insertion sort
- *O(n log n)* - eg. merge sort
- *O(n)* - eg. linear search
- *O(log n)* - eg. binary search
- *O(1)*

`Ω` is the best case, lower bound, same notation as `O` but with `Ω`

- *Ω(n^2)* - eg. selection sort
- *Ω(n log n)* - eg. merge sort
- *Ω(n)* - eg. bubble sort, insertion sort
- *Ω(log n)*
- *Ω(1)* - eg. linear search and binary search

### Calculating O notation

Look at the outer loop,  count how many times it's done
Look at the inner loop, count how many times it's done

It is better to have a better `O` than an `Ω`

If `O` and `Ω (omega)` are the same, their `Θ (theta)` is the same

## Linear search

Going through an array of data, one at a time, starting at the beginning.

```
For i from 0 to n-1
    If i'th element is 50
        Return true
Return false
```

## Binary search

Divide and conquer. Starting at the middle and seeing if the value is less or more than the current one and pick next half to search for.

Only works for sorted arrays.

```
Repeat until the (sub)array is of size 0:
    If no items
        Return false
    Calculate the middle point of the current (sub)array.
        If middle item is 50
            Return true
        Else if 50 < middle item
            Search left half
        Else if 50 > middle item
            Search right half

```

## Bubble sort

```
Set swap counter to a non-zero value (eg. -1)
Repeat until the swap counter is 0:
    Reset swap counter to 0
    For i from 0 to n-2
        If i'th and i+1'th elements out of order
            Swap them
            Add one to the swap counter
```

```
(n - 1) x (n - 2)
n^2 - 2n - 1n + 2
n^2 - 3n + 2
O(n^2)
```

Binary search is better only for sorted arrays, but sorting is more expensive. If you are doing a lot of searching though it makes sense to sort first.

## Selection sort

On each iteration select next smallest element

```
For i from 0 to n-1
    Find smallest item between i'th item and and last item
    Swap smallest item with i'th item
```

```
n(n + 1) / 2
...
O(n^2)
```

## Insertion Sort

Build your sorted array in place, shifting elements out of the way if necessary to make room as you go.

```
Call the first element of the array "sorted."
Repeat until all elements are sorted:
    Look at the next unsorted element. Insert into the "sorted" portion by shifting the requisite number of elements.
```

## Merge sort

The idea of the algorithm is to sort smaller arrays and then combine those arrays together (merge them) in sorted order. Merge sort leverages recursion.

```
If only one item
    Return
Else
    Sort left half of items
    Sort right half of items
    Merge sorted halves (take the smallest element)
```

A process that is dividing into a smaller list is logarithmic.

It comes at the expense of taking up more memory because we have to recombine and create new segments in memory for sub-arrays.

## Custom datatypes

```
// Definition
typedef struct
{
    string name;
    string number;
}
person;

// Usage
person people[2];
people[0].name = "EMMA";
people[0].number = "617-555-0100"
```

## Comparing strings

`strcmp(strarray[index], "VALUE") === 0; // return 0 if found`

## Recursion

Every recursive function has two cases that could apply, given any input

- The _base case_, which when triggered will terminate the recursive process.
- The _recursive case_, which is where the recursion will actually occur.

```
int fact(int n)
{
    if (n == 1)
        return 1;
    else
        return n * fact(n - 1);
}
```

There can be multiple base cases and recursive cases.

Example of multiple base cases is Fibonacci sequence:

- The first element is 0.
- The second element i 1.
- Then nth element is the sum of the (n - 1)th and (n - 2)th elements.

Example of multiple recursive cases is Collatz conjecture. It applies to positive integers and speculates that it is always possible to get "back to 1" if you follow these steps:

- If n is 1, stop.
- Otherwise, if n is even, repeat this process on n/2.
- Otherwise, if n is odd, repeat this process on 3n + 1.

```
#import <stdio.h>
#import <cs50.h>

int collatz(int n);

int main(void)
{
    int n = get_int("n: ");

    printf("%i\n", collatz(n));
}

int collatz(int n)
{
    if (n == 1)
    {
        printf("1\n");
        return 0;
    }

    printf("%i > ", n);

    if (n % 2 == 0)
        return 1 + collatz(n / 2);
    else
        return 1 + collatz(3 * n + 1);
}
```