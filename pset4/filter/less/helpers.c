#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg_float = ((float) image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtRed) / (float) 3;
            image[i][j].rgbtBlue = round(avg_float);
            image[i][j].rgbtGreen = round(avg_float);
            image[i][j].rgbtRed = round(avg_float);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
