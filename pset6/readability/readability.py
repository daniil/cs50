from cs50 import get_string


def main():
    text = get_string("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    grade = calculate_grade(letters, words, sentences)
    print_grade(grade)


# Counts letters in a text by checking for alphanumeric characters only
def count_letters(text):
    count = 0
    for letter in text:
        if (letter.isalpha()):
            count += 1
    return count


# Counts words in a text by splitting on whitespace
def count_words(text):
    return len(text.split())


# Counts sentences in a text by counting '.', '!' or '?'
def count_sentences(text):
    count = 0
    for letter in text:
        if (letter in ['.', '!', '?']):
            count += 1
    return count


# Calculates the grade by applying Coleman-Liau index
def calculate_grade(letters, words, sentences):
    letters_per_100_words = (100 / words) * letters
    sentences_per_100_words = (100 / words) * sentences
    index_float = 0.0588 * letters_per_100_words - 0.296 * sentences_per_100_words - 15.8
    grade_level = round(index_float)
    return grade_level


# Outputs the grade level
def print_grade(grade):
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade {}".format(grade))


if __name__ == "__main__":
    main()