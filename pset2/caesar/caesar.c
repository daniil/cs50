#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool test_argument_valid(int argc, string argv[]);
string convert_to_ciphertext(string plaintext, int key);

int main(int argc, string argv[])
{
    // test if the arguments passed are valid arguments
    if (!test_argument_valid(argc, argv))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    // take user's input and convert it to a ciphertext
    string ciphertext = convert_to_ciphertext(plaintext, atoi(argv[1]));

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

    // only allow positive decimal digits in the argument
    for (int i = 0, arg_len = strlen(argv[1]); i < arg_len; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            return false;
        }
    }
    return true;
}

string convert_to_ciphertext(string ciphertext, int key)
{
    // if the key is larger than 26, wrap around the value
    int key_rounded = key > 26 ? key % 26 : key;

    for (int i = 0, str_len = strlen(ciphertext); i < str_len; i++)
    {
        // only convert alphabetical characters
        if (isalpha(ciphertext[i]))
        {
            // add the key value to a character
            int cipher_char = ciphertext[i] + key_rounded;
            int upper_bound;
            int start_char;

            // define wraparound values for lower and uppercase characters
            if (islower(ciphertext[i]))
            {
                upper_bound = 123;
                start_char = 97;
            }
            else
            {
                upper_bound = 91;
                start_char = 65;
            }

            // if current cipher character is higher than upper bound, wrap it around from start
            if (cipher_char >= upper_bound)
            {
                ciphertext[i] = start_char + (cipher_char - upper_bound);
            }
            else
            {
                ciphertext[i] = cipher_char;
            }
        }
    }

    return ciphertext;
}