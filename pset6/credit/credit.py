# Refactor of pset1/credit
from cs50 import get_string


def main():
    card = get_string("Number: ")

    digit_sum = calculate_digit_sum(card)

    # If digit sum ends with a 0, it's potentially valid CC
    if digit_sum % 10 == 0:
        print(get_card_type(card))
    else:
        print("INVALID")


# Calculates the sum of the digits in the card
def calculate_digit_sum(card):
    card_len = len(card)
    is_even = False
    full_sum = 0

    # Iterate over each character in card number, going backwards
    for i in range(card_len - 1, -1,  -1):
        # cast character to an int
        digit = int(card[i])

        if is_even:
            full_sum += get_even_sum(digit)
        else:
            full_sum += digit

        is_even = not is_even

    return full_sum


# Calculates the sum of digits of even digits multiplied by 2
def get_even_sum(digit):
    return sum(int(mult_digit) for mult_digit in str(digit * 2))


# Returns a CC Card Type based on pattern
def get_card_type(card):
    # AMEX 15 digits, starts with 34 or 37
    if len(card) == 15 and int(card[0:2]) in [34, 37]:
        return "AMEX"

    # MASTERCARD 16 digits, starts with 51, 52, 53, 54, 55
    elif len(card) == 16 and int(card[0:2]) in [51, 52, 53, 54, 55]:
        return "MASTERCARD"

    # VISA 13 or 16 digits, starts with 4
    elif len(card) in [13, 16] and int(card[0]) == 4:
        return "VISA"

    # If none of the CC card starting patterns match, it's invalid
    else:
        return "INVALID"


if __name__ == "__main__":
    main()