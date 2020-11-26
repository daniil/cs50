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

```
If no items
    Return false
If middle item is 50
    Return true
Else if 50 < middle item
    Search left half
Else if 50 > middle item
    Search right half
```

## Big O notation

"On the order of": `O(n)`, `O(log n)`

### Common running times:

`O` is the worst cases, upper bound

O(n^2) - eg. bubble sort, selection sort
O(n log n) - eg. merge sort
O(n) - eg. linear search
O(log n) - eg. binary search
O(1)

`Ω` is the best cases, lower bound, same notation as `O` but with `Ω`

Ω(n^2) - eg. bubble sort, selection sort
Ω(n log n) - eg. merge sort
Ω(n) - eg. bubble sort (better)
Ω(log n)
Ω(1) - eg. linear search and binary search

It is better to have a better `O` than an `Ω`

## Comparing strings

`strcmp(strarray[index], "VALUE") === 0; // return 0 if found`

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

## Bubble sort

```
Repeat n-1 times (better - Repeat until no swaps)
    For i from 0 to n-2
        If i'th and i+1'th elements out of order
            Swap them
```

Look at the outer loop,  count how many times it's done
Look at the inner loop, count how many times it's done

(n - 1) x (n - 2)
n^2 - 2n - 1n + 2
n^2 - 3n + 2
O(n^2)

Bubble sort is better only for sorted arrays, but sorting is more expensive. If you are doing a lot of searching though it makes sense to sort first.

## Selection sort

On each iteration select next smallest element

```
For i from 0 to n-1
    Find smallest item between i'th item and and last item
    Swap smallest item with i'th item
```

n(n + 1) / 2
...
O(n^2)

## Merge sort

```
If only one item
    Return
Else
    Sort left half of items
    Sort right half of items
    Merge sorted halves (take the smallest element)
```

A process that is dividing into a smaller list is logarithmic

If `O` and `Ω (omega)` are the same, their `Θ (theta)` is the same