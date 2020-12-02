#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "helpers.h"

// create a struct to keep Gx and Gy calculation values
typedef struct
{
    int red;
    int green;
    int blue;
}
PIXEL;

RGBTRIPLE blur_pixel(int height, int width, RGBTRIPLE image[height][width], int row, int col);
PIXEL edge_detect(char direction, int height, int width, RGBTRIPLE image[height][width], int row, int col);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create arrays to keep Gx and Gy calculation values
    PIXEL(*Gx_pixels)[width] = calloc(height, width * sizeof(PIXEL));
    PIXEL(*Gy_pixels)[width] = calloc(height, width * sizeof(PIXEL));

    // each row
    for (int i = 0; i < height; i++)
    {
        // each pixel
        for (int j = 0; j < width; j++)
        {
            // run edge detection both for Gx and Gy
            Gx_pixels[i][j] = edge_detect('x', height, width, image, i, j);
            Gy_pixels[i][j] = edge_detect('y', height, width, image, i, j);
        }
    }

    // update original pixels with their edge detected version
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE edge_pixel;

            // Sobel filter algorithm is square root of Gx^2 + Gy^2, do it for each channel
            double red_final = sqrt(pow((double) Gx_pixels[i][j].red, 2) + pow((double) Gy_pixels[i][j].red, 2));
            double green_final = sqrt(pow((double) Gx_pixels[i][j].green, 2) + pow((double) Gy_pixels[i][j].green, 2));
            double blue_final = sqrt(pow((double) Gx_pixels[i][j].blue, 2) + pow((double) Gy_pixels[i][j].blue, 2));

            // cap values at 255 and round the floats into integers
            edge_pixel.rgbtRed = round(fmin(red_final, 255.00));
            edge_pixel.rgbtGreen = round(fmin(green_final, 255.00));
            edge_pixel.rgbtBlue = round(fmin(blue_final, 255.00));

            // set original pixel to an edge pixel version
            image[i][j] = edge_pixel;
        }
    }

    // free allocated memory for Gx and Gy values
    free(Gx_pixels);
    free(Gy_pixels);

    return;
}

PIXEL edge_detect(char direction, int height, int width, RGBTRIPLE image[height][width], int row, int col)
{
    int red_sum = 0;
    int green_sum = 0;
    int blue_sum = 0;

    /*
        Kernel grid for Gx

        -1 0 1
        -2 0 2
        -1 0 1
    */
    int Gx_grid[3][3];

    Gx_grid[0][0] = -1;
    Gx_grid[0][1] = 0;
    Gx_grid[0][2] = 1;
    Gx_grid[1][0] = -2;
    Gx_grid[1][1] = 0;
    Gx_grid[1][2] = 2;
    Gx_grid[2][0] = -1;
    Gx_grid[2][1] = 0;
    Gx_grid[2][2] = 1;

    /*
        Kernel grid for Gy

        -1 -2 -1
         0  0  0
         1  2  1
    */
    int Gy_grid[3][3];

    Gy_grid[0][0] = -1;
    Gy_grid[0][1] = -2;
    Gy_grid[0][2] = -1;
    Gy_grid[1][0] = 0;
    Gy_grid[1][1] = 0;
    Gy_grid[1][2] = 0;
    Gy_grid[2][0] = 1;
    Gy_grid[2][1] = 2;
    Gy_grid[2][2] = 1;

    // go over the 3x3 grid of the pixels, surrounding the current pixel
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // set current row and col of the grid
            int curr_row = row + (i - 1);
            int curr_col = col + (j - 1);
            int kernel = 0;

            // get the kernel value based on x or y direction
            if (direction == 'x')
            {
                kernel = Gx_grid[i][j];
            }
            else if (direction == 'y')
            {
                kernel = Gy_grid[i][j];
            }

            // account for edges of rows and cols, first/last
            if (curr_row >= 0 && curr_col >= 0 && curr_row < height && curr_col < width)
            {
                // multiply each pixel by its G value and take the sum of the resulting values
                red_sum += image[curr_row][curr_col].rgbtRed * kernel;
                green_sum += image[curr_row][curr_col].rgbtGreen * kernel;
                blue_sum += image[curr_row][curr_col].rgbtBlue * kernel;
            }
        }
    }

    PIXEL new_pixel;

    new_pixel.red = red_sum;
    new_pixel.green = green_sum;
    new_pixel.blue = blue_sum;

    return new_pixel;
}
