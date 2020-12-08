// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Multiplier used for hashing function
// 31 is an odd prime helping with avoiding collisions
#define HASH_MULT 31

// Global Variables
FILE *dict_file;

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
bool populate_table(void);
bool add_to_table(char *word);

#endif // DICTIONARY_H
