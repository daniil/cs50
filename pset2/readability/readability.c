// Coleman-Liau index
// index = 0.0588 * L - 0.296 * S - 15.8
// L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string sentence);
int count_words(string sentence);
int count_sentences(string sentence);
int calculate_grade_level(int letter_count, int word_count, int sentence_count);
void output_grade(int grade_level);

int main(void)
{
    string text = get_string("Text: ");

    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);
    int grade_level = calculate_grade_level(letter_count, word_count, sentence_count);

    output_grade(grade_level);
}

int count_letters(string sentence)
{
    int letter_count = 0;

    // using str_len to get length of the string
    for (int i = 0, str_len = strlen(sentence); i < str_len; i++)
    {
        // using isalpha to check if character is alphabetic
        if (isalpha(sentence[i]))
        {
            letter_count++;
        }
    }

    return letter_count;
}

int count_words(string sentence)
{
    // Starting with 1 assuming there is at least one word
    int word_count = 1;

    for (int i = 0, str_len = strlen(sentence); i < str_len; i++)
    {
        // 32 is a space character
        if ((int) sentence[i] == 32)
        {
            word_count++;
        }
    }

    return word_count;
}

int count_sentences(string sentence)
{
    int sentence_count = 0;

    for (int i = 0, str_len = strlen(sentence); i < str_len; i++)
    {
        // . == 46, ! == 33, ? == 63
        if ((int) sentence[i] == 46 ||
            (int) sentence[i] == 33 ||
            (int) sentence[i] == 63)
        {
            sentence_count++;
        }
    }

    return sentence_count;
}

int calculate_grade_level(int letter_count, int word_count, int sentence_count)
{
    float letters_per_100_words = ((float) 100 / (float) word_count) * (float) letter_count;
    float sentences_per_100_words = ((float) 100 / (float) word_count) * (float) sentence_count;
    float index_float = 0.0588 * letters_per_100_words - 0.296 * sentences_per_100_words - 15.8;
    int grade_level = round(index_float);

    return grade_level;
}

void output_grade(int grade_level)
{
    if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }
}
