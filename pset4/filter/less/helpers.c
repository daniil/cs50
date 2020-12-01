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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float original_red = (float) image[i][j].rgbtRed;
            float original_green = (float) image[i][j].rgbtGreen;
            float original_blue = (float) image[i][j].rgbtBlue;

            float sepia_red = fmin(.393 * original_red + .769 * original_green + .189 * original_blue, 255.00);
            float sepia_green = fmin(.349 * original_red + .686 * original_green + .168 * original_blue, 255.00);
            float sepia_blue = fmin(.272 * original_red + .534 * original_green + .131 * original_blue, 255.00);

            image[i][j].rgbtBlue = round(sepia_blue);
            image[i][j].rgbtGreen = round(sepia_green);
            image[i][j].rgbtRed = round(sepia_red);
        }
    }
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
