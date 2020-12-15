from sys import argv, exit
import cs50


def main():
    if (len(argv) != 2):
        print("Usage: python roster.py <house name>")
        exit(1)

    # Connect to DB
    db = cs50.SQL("sqlite:///students.db")

    output_students(db, argv[1])


# Prints full name and birth year of all students in the house
def output_students(db, house):
    # Select students for current house
    students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)

    for student in students:
        # Convert student name fields into a full name
        name = get_full_name(student)
        print(f"{name}, born {student['birth']}")


# Returns a full name of the student
def get_full_name(student):
    if (student['middle']):
        name = f"{student['first']} {student['middle']} {student['last']}"
    else:
        name = f"{student['first']} {student['last']}"

    return name


if __name__ == "__main__":
    main()