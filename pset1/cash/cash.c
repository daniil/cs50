#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float userChange;

    // Only allow positive input
    do
    {
        userChange = get_float("Change owed: ");
    }
    while (userChange < 0);

    // Round up the cents after conversion
    int cents = round(userChange * 100);
    int numberOfCoins = 0;

    // Reduce number of cents, going highest first
    // while counting number of coins requires
    while (cents > 0)
    {
        if (cents >= 25)
        {
            cents -= 25;
        }
        else if (cents >= 10)
        {
            cents -= 10;
        }
        else if (cents >= 5)
        {
            cents -= 5;
        }
        else
        {
            cents -= 1;
        }

        numberOfCoins ++;
    }

    printf("%i\n", numberOfCoins);
}