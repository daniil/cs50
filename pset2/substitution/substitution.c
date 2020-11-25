#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool test_argument_valid(int argc, string argv[]);
bool check_char_unique(string argv);
string convert_to_ciphertext(string text, string key);

int main(int argc, string argv[])
{
    // test if the arguments passed are valid arguments
    if (!test_argument_valid(argc, argv))
    {
        printf("Usage: `./substitution key`. Key must contain 26 unique characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    string ciphertext = convert_to_ciphertext(plaintext, argv[1]);

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool test_argument_valid(int argc, string argv[])
{
    // only allow one command-line argument, the key
    if (argc != 2)
    {
        return false;
    }

    string key = argv[1];

    // key has to be exactly 26 characters
    if (strlen(key) != 26)
    {
        return false;
    }

    // only allow alphabetic characters in the argument
    for (int i = 0, key_len = strlen(key); i < key_len; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }

    // check each character for uniqueness
    if (!check_char_unique(key))
    {
        return false;
    }

    return true;
}

bool check_char_unique(string key)
{
    // create an array to keep seen letters
    char seen_it[26];

    for (int i = 0, key_len = strlen(key); i < key_len; i++)
    {
        // check seen letters array for repeats
        for (int j = 0; j < strlen(seen_it); j++)
        {
            // when comparing, normalize the case of both characters to upper
            if (toupper(key[i]) == toupper(seen_it[j]))
            {
                // return false if there is a repeat
                return false;
            }
        }

        // keep current letter in a seen letter array
        seen_it[i] = key[i];
    }

    // return true if no repeats have been found
    return true;
}

string convert_to_ciphertext(string text, string key)
{
    for (int i = 0, text_len = strlen(text); i < text_len; i++)
    {
        char currChar = text[i];

        // only convert alphabetical characters
        if (isalpha(currChar))
        {
            // separate upper and lower case characters to account for different offsets
            // when substituting the character with key character, match the case
            if (isupper(currChar))
            {
                text[i] = toupper(key[currChar - 65]);
            }
            else
            {
                text[i] = tolower(key[currChar - 97]);
            }
        }
    }

    return text;
}
