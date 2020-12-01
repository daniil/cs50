#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "helpers.h"

RGBTRIPLE blur_pixel(int height, int width, RGBTRIPLE image[height][width], int row, int col);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // each row
    for (int i = 0; i < height; i++)
    {
        // each pixel
        for (int j = 0; j < width; j++)
        {
            // for greyscale conversion set RGB values to be the same, and average of RGB of each pixel
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
    // each row
    for (int i = 0; i < height; i++)
    {
        // each pixel
        for (int j = 0; j < width; j++)
        {
            float original_red = (float) image[i][j].rgbtRed;
            float original_green = (float) image[i][j].rgbtGreen;
            float original_blue = (float) image[i][j].rgbtBlue;

            // apply a sepia formula to each color byte
            float sepia_red = fmin(.393 * original_red + .769 * original_green + .189 * original_blue, 255.00);
            float sepia_green = fmin(.349 * original_red + .686 * original_green + .168 * original_blue, 255.00);
            float sepia_blue = fmin(.272 * original_red + .534 * original_green + .131 * original_blue, 255.00);

            // set new values for each color byte
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
    for (int i = 0; i < height; i++)
    {
        // allocate heap memory for each row
        RGBTRIPLE *flippedRow = malloc(width * sizeof(RGBTRIPLE));

        // add flipped pixels to flippedRow
        for (int j = 0; j < width; j++)
        {
            flippedRow[j] = image[i][width - j - 1];
        }

        // set original image pixels to their flippedRow positions
        for (int j = 0; j < width; j++)
        {
            image[i][j] = flippedRow[j];
        }

        // free allocated heap memory
        free(flippedRow);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // allocate heap memory for blurred_pixels 2d array
    RGBTRIPLE(*blurred_pixels)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // each row
    for (int i = 0; i < height; i++)
    {
        // each pixel
        for (int j = 0; j < width; j++)
        {
            // generate blurred pixels bases on original color values
            blurred_pixels[i][j] = blur_pixel(height, width, image, i, j);
        }
    }

    // iterate over blurred pixels and update original image values with blurred values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurred_pixels[i][j];
        }
    }

    // free allocated heap memory
    free(blurred_pixels);

    return;
}

RGBTRIPLE blur_pixel(int height, int width, RGBTRIPLE image[height][width], int row, int col)
{
    int val_count = 0;

    float red_sum = 0;
    float green_sum = 0;
    float blue_sum = 0;

    // go over the 3x3 grid of the pixels, surrounding the current pixel
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // pick a current row and col of the grid
            int curr_row = row + (i - 1);
            int curr_col = col + (j - 1);

            // account for edges of rows and cols, first/last
            if (curr_row >= 0 && curr_col >= 0 && curr_row < height && curr_col < width)
            {
                red_sum += (float) image[curr_row][curr_col].rgbtRed;
                green_sum += (float) image[curr_row][curr_col].rgbtGreen;
                blue_sum += (float) image[curr_row][curr_col].rgbtBlue;

                val_count++;
            }
        }
    }

    // create a pixel struct and calculate the average for the pixel
    RGBTRIPLE new_pixel;

    new_pixel.rgbtBlue = round(blue_sum / (float) val_count);
    new_pixel.rgbtGreen = round(green_sum / (float) val_count);
    new_pixel.rgbtRed = round(red_sum / (float) val_count);

    return new_pixel;
}