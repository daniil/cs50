## Memory Allocation Review

A pointer is an address in memory and an array is just a chunk of memory. We can use it interchangeably in certain contexts.
If you use a square bracket next to a pointer it will point to the correct address in memory.

```
#include <stdio.h>
#include <stdlib.h> // where malloc and free defined

int main(void)
{
    int *list = malloc(3 * sizeof(int));

    // always check if you have enough memory
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // reallocate the memory
    int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL)
    {
        return 1;
    }

    list = tmp;
    tmp[3] = list[4];

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    // free the memory once we are done with it
    free(list);
}
```

## Linked List

A linked list is a data structure containing multiple chunks of memory that are linked together by the way of pointers.

```
// have to define it with formal name if you are using it inside of struct itself
// formal name for the structure
typedef struct node
{
    int number;
    struct node *next;
}
node; // nickname for the struct

// usage

node *list = NULL;

node *n = malloc(sizeof(node));
if (n != NULL)
{
   (*n).number = 2; // parentheses required for order of operations
    n->number = 2; // syntactic (preferred) sugar
    n->next = NULL;
}

// update a list to point to first node
list = n;

// iterating over a linked list
node *tmp = list;
while (tmp->next != NULL)
{
    tmp = tmp->next;
}
```

The benefit of linked list is ability to do dynamic insertion.
Linked list come at a cost of losing the random access (ie: square bracket / index syntax).

Running time of linked list

```
O(n) - search, insert
```

Linked list `for` loop

```
for (node *tmp = list; tmp != NULL; tmp = tmp->next)
```

Freeing a linked list

```
while (list != NULL)
{
    node *tmp = list->next;
    free(list);
    list = tmp;
}
```

## Trees

### Binary Search Tree

```
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;
```

First top node is called a root node.
This data structure gains us back the ability to do binary search, because by definition left node is always smaller than the right node.
Trees are recursive data structures.

```
bool search(node *tree)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (50 < tree->number)
    {
        return search(tree->left);
    }
    else if (50 > tree->number)
    {
        return search(tree->right);
    }
    else
    {
        return true;
    }
}
```

Running time of binary tree

```
O(log n) - search, insert
```

## Hash Tables

A hash table is a combination of an array and linked lists inside of it.

Hash function is the function that decides which bucket the value goes in.

With hash tables there is a balance of space and time complexity, creating more buckets for uniqueness to approach `O(1)` or having each bucket as a linked list that requires lookup of `O(n)`.

## Tries

It uses a lot more memory but allows us constant lookup time - `O(1)`.

It's essentially an array of arrays, one for each character of a string for example.

```
[
    [a,
        [a, b,
            [a, b, c, d]
        ]
    ],
    [b, c],
    c
]
```

## Abstract Data Structures

### Queues

FIFO - first in, first out.
enqueue means to get in line.
dequeue means to get out of line.

### Stacks

LIFO - last in, first out.
push - to add to stack.
pop - to remove from stack.

### Dictionaries

A key value pair.