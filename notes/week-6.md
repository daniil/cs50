## General Python rules

- no semicolons, but indentation matters
- no explicit data types, but declared by initialization only
- there is no upper bounds to an int, no overflow problems

## Getting user input and printing it

```
from cs50 import get_string

answer = get_string("What's your name?\n")
print("hello" + answer) # concatenation
print("hello", answer) # multiple arguments
print(f"hello, {answer}") # format string
```

## Defining and incrementing variables

```
counter = counter + 1
counter += 1
```

No `counter++` however

## Operators

`||` is `or`
`&&` is `and`
`!` is `not`

## If, if/else statements

```
if x < y:
    print("x is less than y")
elif x > 1:
    print("x is greater than y")
else
    print("x is equal to y")
```

## Loops

```
while True:
    print("hello world")

i = 3
while i > 0:
    print("cough")
    i -= 1

# there is no "do/while" loop
```

```
for i in [0, 1, 2]:
    print("cough")

for i in range(3):
    print("cough")

for x in range(0, 100, 2): # additional range params
    print(x)
```

## Data Types

- bool
- int
- float
- str
- range - sequence of numbers
- list - sequence of mutable values
- tuple - sequence of immutable values
- dict - collection of key/value pairs
- set - collection of unique values

## Lists

```
scores = []
scores.append(72)
scores.append(73)
scores.append(33)

# or
scores = [72, 73, 33]

# or
scores = list()

print(f"Average: ${sum(scores) / len(scores)}")

# list comprehension
nums = [x for x in range(500)]
```

### List Methods

```
nums = [1, 2, 3, 4]
nums.append(5) # add to the end
nums.insert(4, 5) # insert at specific position
nums[len(nums):] = [5] # splicing list into another list
```

## Tuples

```
# list of tuples
presidents = [
    ("George Washington", 1789),
    ("John Adams", 1797),
    ("Thomas Jefferson", 1801),
    ("James Madison", 1809)
]

# iterating over tuples
for prez, year in presidents:
    print("In {1}, {0} took office".format(prez, year))
```

## Dictionaries

```
from sys import exit

people = {
    "EMMA": "617-555-0100",
    "RODRIGO": "617-555-0101",
    "BRIAN": "617-555-0102",
    "DAVID": "617-555-0103"
}

# setting new value
people["CRAIG"] = "617-555-0104"

if "EMMA" in people:
    print(f"Found {people['DAVID']}")
    exit(0)
exit(1)

# iterating over keys
for person in people:
    print(person)

# iterating over keys and values (does not guarantee the order)
for person, phone in people.items():
    print("{}'s phone number is {}".format(person, phone))
```

## Functions

```
# using a main function
if __name__ == "__main__":
    main()
```

### Definition

```
def square(x):
    return x ** 2 # exponentiation operator
```

## Objects

```
class Student():

    def __init__(self, name, id):
        self.name = name
        self.id = id

    def changeID(self, id):
        self.id = id

    def print(self):
        print("{} - {}".format(self.name, self.id))

# using objects
jane = Student("Jane", 10)
jane.print()
jane.changeID(11)
jane.print()
```

## Examples

### Blur Filter

```
from PIL import Image, ImageFilter

before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.BLUR)
after.save("out.bmp")
```

### Spell Check

```
words = set()

def check(word):
    if word.lower() in words:
        return True
    else:
        return False

def load(dictionary):
    file = open(dictionary, "r")
    for line in file:
        words.add(line.rstrip("\n")) # remove from end of string
    file.close()
    return True

def size():
    return len(words)

def unload():
    return True
```

### Agreement

```
from cs50 import get_string

s = get_string("Do you agree \n")

if s.lower() in ["y", "yes"]:
    print("Agreed")
elif s.lower() in ["n", "no"]:
    print("Not agreed")
```

### Function Definitions

```
def main():
    cough(3)

def cough(n):
    for in range(n):
        print("cough")

main()
```

### Conditional Loop

```
def get_positive_int():
    while True:
        n = get_int("Positive Integer: ")
        if n > 0:
            break
    return n # the variable will be available even if it's inside of a while loop (or other level of indentation)
```

### Named arguments

```
for i in range(4)
    print("?", end="") # default end is "\n"
print()

# more Pythonic
print("?" * 4)
```

### Getting input without cs50 library

```
# input automatically outputs a string
s = input("What's your name?\n")
print(f"Hello, {s}")

# casting
age = int(input("What's your age?\n"))
print(f"You are at least ${age * 365} days old")
```

### Iterating Over Characters

```
from cs50 import get_string

s = get_string("Input: ")
print("Output: ", end="")
for i in range(len(s)):
    print(s[i], end="")
print()

# or
for c in s:
    print(c, end="")
print()
```

### Command Line Arguments

```
from sys import argv

for i in range(len(argv)):
    print(argv[i])

# or
for arg in argv:
    print(arg)
```

### Linear Search

```
from sys import exit

names = ["EMMA", "RODRIGO", "BRIAN", "DAVID"]

if "EMMA" in names:
    print("Found")
    exit(0)
print("Not found")
exit(1)
```

### Comparing Strings

```
string1 == string2
```

### Swap

```
x = 1
y = 2
x, y = y, x
```

### Files

```
import csv
from cs50 import get_string

name = get_string("Name: ")
number = get_string("Number: ")

with open("phonebook.csv", "a"): # you don't have to close the file manually
    writer = csv.writer(file)
    writer.writerow((name, number)) # takes a tuple
```

## Regular Expressions

- `.` - any character
- `.*` - 0 or more characters
- `.+` - 1 or more characters
- `?` - optional
- `^` - start of input
- `$` - end of input
- `|` - or
- `()` - group

```
if re.search("^y(es)?$", s, re.IGNORECASE):
    print("Agreed.")
elif re.search("n(o)?", s):
    print("Not agreed.")
```