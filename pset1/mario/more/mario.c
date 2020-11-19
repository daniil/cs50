#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int colNum;

    // Ask user for input and only take integers between 1 and 8
    do
    {
        colNum = get_int("Height: ");
    }
    while (colNum < 1 || colNum > 8);

    // Iterate over supplied number, this loop is for each row
    for (int i = 0; i < colNum; i++)
    {
        // Print right aligned column
        for (int j = 0; j < colNum; j++)
        {
            // Add spaces for total columns - current column 
            // and keep one, based on current row number
            printf(colNum - j - 1 > i ? " " : "#");
        }

        // Print empty spaces
        printf("  ");

        // Print left aligned column
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // Print new row
        printf("\n");
    }
}