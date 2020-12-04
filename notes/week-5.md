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

Once you create a list you want to keep track of it's head node to be able to refer to it.

```
// self-referential data type
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

### Link List Operations

#### Create a linked list

```
sllnode* create(VALUE val);
```

1. Dynamically allocate space for a new `sllnode`
2. Check to make sure we didn't run out of memory
3. Initialize the node's `val` field
4. Initialize the node's `next` field (`NULL`)
5. Return a pointer to the newly created `sllnode`

#### Search through a linked list

```
bool find(sllnode* head, VALUE val);
```

1. Create a traversal pointer (`trav`) pointing to the list's head (don't use the head pointer to avoid accidents)
2. If the current node's `val` field is what we're looking for, report success
3. If not, set the travelsal pointer to the next pointer in the list and go back to step 2
4. If you've reached the end of the list, report failure

#### Insert a new node into the linked list

```
sllnode* insert(sllnode* head, VALUE val);
```

1. Dynamically allocate space for a new `sllnode`
2. Check to make sure we didn't run out of memory
3. Populate and insert the node *at the beginning of the linked list*
4. Return a pointer to the new head of the linked list

#### Delete an entire linked list

```
void destroy(sllnode* head);
```

1. If you've reached a `NULL` pointer, stop
2. Delete the rest of the list
3. Free the current node

### Running time of linked list

```
O(n) - search, insert
```

### Linked list `for` loop

```
for (node *tmp = list; tmp != NULL; tmp = tmp->next)
```

### Freeing a linked list

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

Hash tables are similar to a regular key-value pair data store, but in hash table the generation of the keys makes hash tables unique. Keys are generated with special process called hashing (hash function).

Hash function is the function that decides at which index of the array the value goes in.

With hash tables there is a balance of space and time complexity, creating more buckets for uniqueness to approach `O(1)` or having each bucket as a linked list that requires lookup of `O(n)`.

A good hash function should:

- Use only the data being hashed
- Use all of the data being hashed
- Be deterministic
- Uniformly distribute data
- Generate very different hash codes for very similar data

Example (slightly naive implementation):

```
unsigned int hash(char* str)
{
    int sum = 0;
    for (int j = 0; str[j] != '\0'; j++)
    {
        sum += str[j];
    }
    return sum % HASH_MAX; // HASH_MAX being the size of the hash map array
}
```

You don't usually need to write your own hash function, there are a lot of good open source ones.

### Collisions

If a hash function returns the value that is already occupied, that is known as a *collision*.

One way to resolve a collision is by _Linear probing_. In this method if we have a collision we try to place the data in the next consecutive element in the array (wrapping around to the beginning if necessary) until we find a vacancy.

Linear probing is subject to a problem called *clustering*. Once there is a miss, two adjacent cells will contain data, making it more likely in the future that the cluster will grow.

Another way to resolve collisions is by _Chaining_. If each element of the array is a pointer to the head of a linked list, then multiple pieces of data can yield the same hash code.

## Tries

Tries combine structures and pointers together to store data. The data to be searched for in the trie is a roadmap.

It's essentially an array of arrays, one for each character of a string or integer for example.

It uses a lot more memory but allows us constant lookup time - `O(1)`.

In a trie, the paths from a central *root* node (globally declared) to a *leaf* node are labeled with individual character of a key (digit or character). Each node on the path from root to leaf can have multiple pointers emanating from it, one for each character or digit.

To insert an element into the trie, we need to build the correct path from the root to the leaf.

```
typedef struct _trie
{
    char value[20]; // 20 is a string limit we want to store in this specific case
    struct _trie* paths[10]; // 10 is for 10 digits of 0-9 for a key
}
trie;
```

To search for an element in the trie, use successive characters or digits to navigate from the root. If you make it to the end without hittind a `NULL` pointer, output the value at that node.

## Abstract Data Structures

### Queues

- FIFO - first in, first out.
- enqueue - insert element to the end of the queue.
- dequeue - remove element from the front of the queue.

### Stacks

- LIFO - last in, first out.
- push - insert element to the top of the stack.
- pop - remove element from the top of the stack.

### Dictionaries

A key value pair.

## Summary

### Arrays

- Insertion is bad - lots of shifting to fit an element in the middle
- Deletion is bad - lots of shifting after removing an element
- Lookup is great - random access, constant time
- Relatively easy to sort
- Relatively small size-wise
- Stuck with a fixed size, no flexibility

### Linked Lists

- Insertion is easy - just tack onto the front
- Deletion is easy - once you find the element
- Lookup is bad - have to rely on linear search
- Relatively difficult to sort - unless you're willing to compromise on super-fast insertion and instead sort as you construct
- Relatively small size-wise (not as small as arrays)

### Hash Tables

- Insertion is a two-step process - hash, then add
- Deletion is easy - once you find the element
- Lookup is on average better than with linked lists because you have the benefit of a real-world constant factor
- Not an ideal data structure if sorting is the goal - just use an array
- Can run the gamut of size

### Tries

- Insertion is complex - a lot of dynamic memory allocation, but gets easier as you go
- Deletion is easy - just free a node
- Lookup is fast - not quite as fast as an array, but almost
- Already sorted - sorts as you build in almost all situations
- Rapidly becomes huge, even with very little data present, not great if space is at a premium