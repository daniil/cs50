#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long cc;

    do
    {
        cc = get_long("Number: ");
    }
    while (cc < 0);

    long sum = 0;

    // Iterate for up to 16 decimal places, going two at a time
    for (long i = 10; i < 100000000000000000; i *= 100)
    {
        // Get every other digit, starting with second to last
        long secondFromEnd = (cc / i) % 10;

        // Get every other digit, starting from last
        long firstFromEnd = (cc / (i / 10)) % 10;

        // Multiply secondFromEnd digits by 2
        long mult2 = secondFromEnd * 2;

        // Add mult2 product's digits to a sum, ie 18 = 1 + 8, 6 = 0 + 6
        // and then add firstFromEnd digits that are not multiplied
        sum += mult2 / 10 + mult2 % 10 + firstFromEnd;
    }

    // Check if checksum validates
    long isCardValid = sum % 10 == 0;

    if (isCardValid)
    {
        // AMEX 15 digits, starts with 34 or 37 - divide by 10000000000000
        if (cc / 10000000000000 == 34 || cc / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }

        // MASTERCARD 16 digits, starts with 51, 52, 53, 54, 55 - divide by 100000000000000
        else if (cc / 100000000000000 == 51 ||
                 cc / 100000000000000 == 52 ||
                 cc / 100000000000000 == 53 ||
                 cc / 100000000000000 == 54 ||
                 cc / 100000000000000 == 55)
        {
            printf("MASTERCARD\n");
        }

        // VISA 13 or 16 digits, starts with 4 - divide by 1000000000000000 || 1000000000000
        else if (cc / 1000000000000000 == 4 || cc / 1000000000000 == 4)
        {
            printf("VISA\n");
        }

        // If none of the CC card starting patterns match, it's also invalid
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
