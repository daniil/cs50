// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10001;

// Hash table
node *table[N];

// Dictionary word count, defaulted to 0
unsigned int dict_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Iterate over all words that belong to that hash
    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        // Compare strings ignoring case and return true if word is found
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }

    // Word is not found in dictionary return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashval;

    // Iterate over each character in the word
    for (hashval = 0; *word != '\0'; word++)
    {
        // Lower case the character to ensure non-cased string comparison
        hashval = tolower(*word) + HASH_MULT * hashval;
    }

    return hashval % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // Generate hash table
    populate_table();

    return true;
}

// Generates a dictionary hash table with words
bool populate_table(void)
{
    int index = 0;
    char word[LENGTH + 1];

    // Iterate over each string of the file
    while (fscanf(dict_file, "%s", word) != EOF)
    {
        // Count words
        dict_words++;

        // Add new word to dictionary table
        add_to_table(word);
    }

    return true;
}

// Adds a word to the dictionary table
bool add_to_table(char *word)
{
    struct node *tmp;
    unsigned int hashval;

    tmp = (struct node *) malloc(sizeof(*tmp));
    if (tmp == NULL)
    {
        return false;
    }

    // Copy word into the node
    strcpy(tmp->word, word);

    // Calculate the hash of the word
    hashval = hash(word);

    if (table[hashval] == NULL)
    {
        // If there is no node at current hash table value, set next of node to NULL
        tmp->next = NULL;
    }
    else
    {
        // Set temp node's next pointer to current head node of the hash table at hash value
        tmp->next = table[hashval];
    }

    // Set hash table at hash value to temp node
    table[hashval] = tmp;

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // We already calculate the length while loading, we can return it right away
    return dict_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate over hash table
    for (int i = 0; i < N; i++)
    {
        // Check if table not NULL
        if (table[i] == NULL)
        {
            continue;
        }

        // Free hash table nodes going until the last node is NULL
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        // Free the last node as well
        free(cursor);
    }

    // Close the dictionary file
    fclose(dict_file);

    return true;
}
