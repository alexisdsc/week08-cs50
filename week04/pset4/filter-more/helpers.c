#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE red, green, blue, average_gray;
    // iterate over every row of the image
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Get the value of every pixel
            blue = image[row][col].rgbtBlue;
            green = image[row][col].rgbtGreen;
            red = image[row][col].rgbtRed;
            // Get the average of the pixels
            average_gray = (BYTE) round((blue + green + red) / 3.0);
            // Assign the new average to every pixel
            image[row][col].rgbtBlue = average_gray;
            image[row][col].rgbtGreen = average_gray;
            image[row][col].rgbtRed = average_gray;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    temp.rgbtBlue = 0;
    temp.rgbtGreen = 0;
    temp.rgbtRed = 0;
    int half_width = 0;
    int original_col, opposite_col;

    // Check if rows have odd or even number of pixels
    if (width % 2 == 0)
    {
        half_width = (int)(width / 2.0);
    }
    else
    {
        half_width = ((int)round((width / 2.0))) - 1;
    }

    // Reflect every row of the image
    for (int row = 0; row < height;  row++)
    {
        // swap the pixels
        for (int col = 0; col < half_width; col++)
        {
            original_col = col;
            opposite_col = (width - 1) - col;

            // Blue pixel swap
            temp.rgbtBlue = image[row][original_col].rgbtBlue;
            image[row][original_col].rgbtBlue = image[row][opposite_col].rgbtBlue;
            image[row][opposite_col].rgbtBlue = temp.rgbtBlue;
            // Green pixel swap
            temp.rgbtGreen = image[row][original_col].rgbtGreen;
            image[row][original_col].rgbtGreen = image[row][opposite_col].rgbtGreen;
            image[row][opposite_col].rgbtGreen = temp.rgbtGreen;
            // Red pixel swap
            temp.rgbtRed = image[row][original_col].rgbtRed;
            image[row][original_col].rgbtRed = image[row][opposite_col].rgbtRed;
            image[row][opposite_col].rgbtRed = temp.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image
    RGBTRIPLE tempimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempimage[i][j] = image[i][j];
        }
    }

    // Blur Every Pixel - Get the average of their neighbors
    // Declare variables
    int red, green, blue;
    int average = 0;
    float pixel_counter;

    // Iterate over the rows
    for (int row = 0; row < height; row++)
    {
        // Iterate over the columuns
        for (int col = 0; col < width; col++)
        {
            // Set initial values
            red = 0;
            green = 0;
            blue = 0;
            pixel_counter = 0.0;

            // Iterate over the rows next to it
            for (int r = -1; r < 2; r++)
            {
                // iterate over the columns next to it
                for (int c = -1; c < 2; c++)
                {
                    // skip pixel if out of the range of the image
                    // check if current pixel out of height range
                    if (row + r < 0 || row + r >= height)
                    {
                        continue;
                    }
                    // check if pixel out of width range
                    if (col + c < 0 || col + c >= width)
                    {
                        continue;
                    }
                    // Otherwise add up the pixel
                    red += tempimage[row + r][col + c].rgbtRed;
                    green += tempimage[row + r][col + c].rgbtGreen;
                    blue += tempimage[row + r][col + c].rgbtBlue;
                    pixel_counter++;
                }
            }
            // Get and assign the evarage of every pixel
            image[row][col].rgbtRed = (BYTE) round(red / pixel_counter);
            image[row][col].rgbtGreen = (BYTE) round(green / pixel_counter);
            image[row][col].rgbtBlue = (BYTE) round(blue / pixel_counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image
    RGBTRIPLE tempimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempimage[i][j] = image[i][j];
        }
    }

    // Define variables
    int red, green, blue;
    int gxred, gxgreen, gxblue;
    int gyred, gygreen, gyblue;
    int grow, gcol;

    // Define Gx and Gy and set their values
    // Gx
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // Gy
    int gy[3][3] = {{-1, -2, -1}, { 0, 0, 0}, { 1, 2, 1}};

    // Apply kernels Gx and Gy to every pixel
    // Iterate over every row
    for (int row = 0; row < height; row++)
    {
        // Iterate over every column
        for (int col = 0; col < width; col++)
        {
            // Set initial values
            gxred = 0;
            gxgreen = 0;
            gxblue = 0;
            gyred = 0;
            gygreen = 0;
            gyblue = 0;
            // Reset the rows for the G kernels
            grow = 0;

            // Iterate over every pixel around the current pixel
            // Rows next to it (top to down)
            for (int r = -1; r < 2; r++)
            {
                // Reset the columns for the G kernels
                gcol = 0;

                // Columns next to it (left to right)
                for (int c = -1; c < 2; c++)
                {
                    // count every pixel around
                    // Treat as black every pixel put of the range of the image -- add zero
                    if (row + r < 0 || row + r >= height)
                    {
                        continue;
                    }
                    if (col + c < 0 || col + c >= width)
                    {
                        gcol++;
                        continue;
                    }

                    // Multiply by Gx values
                    gxred += tempimage[row + r][col + c].rgbtRed * gx[grow][gcol];
                    gxgreen += tempimage[row + r][col + c].rgbtGreen * gx[grow][gcol];
                    gxblue += tempimage[row + r][col + c].rgbtBlue * gx[grow][gcol];
                    // Multiply by Gy values
                    gyred += tempimage[row + r][col + c].rgbtRed * gy[grow][gcol];
                    gygreen += tempimage[row + r][col + c].rgbtGreen * gy[grow][gcol];
                    gyblue += tempimage[row + r][col + c].rgbtBlue * gy[grow][gcol];

                    // Next column
                    gcol++;
                }
                // Next row
                grow++;
            }

            // Compute the square root of (Gx^2 + Gy^2)
            red = (int) round(sqrt(gxred * gxred + gyred * gyred));
            green = (int) round(sqrt(gxgreen * gxgreen + gygreen * gygreen));
            blue = (int) round(sqrt(gxblue * gxblue + gyblue * gyblue));

            // Limit to 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // Set the values to the current pixel
            image[row][col].rgbtRed = red;
            image[row][col].rgbtGreen = green;
            image[row][col].rgbtBlue = blue;
        }
    }

    return;
}
