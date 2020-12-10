from cs50 import get_string


def main():
    input = get_string("What is your name?\n")
    print("hello, {}".format(input))


if __name__ == "__main__":
    main()