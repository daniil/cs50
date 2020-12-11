from sys import argv, exit
import csv
import re


def main():
    # Check command-line arguments for DB and sequence files
    if (len(argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Extract filenames from the arguments
    db_filename = argv[1]
    sequence_filename = argv[2]

    # Get sequence from a file
    sequence = get_sequence(sequence_filename)

    # Run sequence through database
    person_match = check_db(db_filename, sequence)

    # Print a matched person or No match
    print(person_match)


# Returns a DNA sequence read from a file
def get_sequence(file):
    with open(file) as f:
        return f.read()


# Returns matched person or no match for a DNA sequence in the DB file of matches
def check_db(file, sequence):
    with open(file) as f:
        curr_match = 'No match'

        strs = []
        reader = csv.DictReader(f)
        for person in reader:
            # Get STRs once
            if not strs:
                strs = get_strs(person)

            # Count the number of matches of each STR in a sequence
            matches = count_matches(person, sequence, strs)

            # If all STRs match, this person is a DNA match
            if (matches == len(strs)):
                curr_match = person['name']

        return curr_match


# Returns STRs list from a CSV row
def get_strs(row):
    strs = []

    # Iterate over CSV row keys
    for key in row.keys():
        # Append all keys except for name
        if (key != 'name'):
            strs.append(key)

    return strs


# Returns a count of consecutive STR matches in a sequence
def count_matches(person, sequence, strs):
    match_count = 0

    for str in strs:
        # Get a count of current STR in a sequence
        str_count = get_str_count(sequence, str)

        # If STR count in DB matches the count in sequence, increment
        if (int(person[str]) == str_count):
            match_count += 1

    return match_count


def get_str_count(sequence, str):
    # Find all matches of consecutive STR in a sequence
    matches = re.findall(r"(?:{})+".format(str), sequence)

    if matches:
        # Find the largest consecutive string
        largest = max(matches, key=len)

        # Calculate the length
        str_count = len(largest) // len(str)
    else:
        return 0

    return str_count


if __name__ == "__main__":
    main()