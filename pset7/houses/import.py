from sys import argv, exit
import cs50
import csv


def main():
    if len(argv) != 2:
        print("Usage: python import.py <filename>.csv")
        exit(1)

    # Connect to DB
    db = cs50.SQL("sqlite:///students.db")

    # Clean up the table
    db.execute("DELETE FROM students")

    # Populate DB
    populate_db(db, argv[1])


# Populates DB with values from CSV
def populate_db(db, csv_file):
    with open(csv_file, "r") as character:
        reader = csv.DictReader(character)

        for row in reader:
            name = extract_name(row)

            # Execute an INSERT query
            db.execute("INSERT INTO students (first, middle, last, birth, house)  VALUES(?, ?, ?, ?, ?)",
                       name['first'], name['middle'], name['last'], int(row['birth']), row['house'])


# Extract first, middle and last name from the full name string
def extract_name(row):
    name = {
        'first': '',
        'middle': None,
        'last': ''
    }

    # Split full name string into a list
    name_list = row['name'].split()

    name['first'] = name_list[0]
    name['last'] = name_list[-1]

    # Set the middle name only if it's part of the name
    if len(name_list) == 3:
        name['middle'] = name_list[1]

    return name


if __name__ == "__main__":
    main()