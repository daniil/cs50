#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int colNum;

    do
    {
        colNum = get_int("Height: ");
    }
    while (colNum < 1 || colNum > 8);

    for (int i = 0; i < colNum; i++)
    {
        for (int j = 0; j < colNum; j++)
        {
            // 0: 0 1 2  ..#
            // 1: 0 1 2. .##
            // 2: 0 1 2  ###

            if (colNum - j - 1 > i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}