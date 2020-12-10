# Refactor of pset1/mario/more
from cs50 import get_int


def main():
    # Iterate until user inputs correct value
    while(True):
        cols = get_int("Height: ")

        # Input needs to be between 1-8
        if cols > 0 and cols < 9:
            break

    # Print the pyramid
    print_pyramid(cols)


# Prints equal size pyramid
def print_pyramid(cols):
    for i in range(1, cols + 1):
        print(" " * (cols - i), end="")
        print("#" * i, end="")
        print(" " * 2, end="")
        print("#" * i)

        # one liner
        # print("{}{}  {}".format(" " * (cols - i), "#" * i, "#" * i))


if __name__ == "__main__":
    main()