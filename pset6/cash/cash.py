# Refactor of pset1/cash
from cs50 import get_float


def main():
    while True:
        change = get_float("Change owed: ")

        # Keep asking until valid number is provided
        if (change > 0):
            break

    # Print number of coins
    print(coins_num(change))


def coins_num(change):
    coin_count = 0
    cents = round(change * 100)

    # Reduce the change starting with larger coins
    while cents > 0:
        if cents >= 25:
            cents -= 25
        elif cents >= 10:
            cents -= 10
        elif cents >= 5:
            cents -= 5
        else:
            cents -= 1

        coin_count += 1

    return coin_count


if __name__ == "__main__":
    main()