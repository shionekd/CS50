#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            double doubleAvg = (image[i][j].rgbtRed +
                                image[i][j].rgbtGreen +
                                image[i][j].rgbtBlue)
                                / 3.0;
            int avg = round(doubleAvg);
            // Update pixel values
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // Update pixel with sepia values
            if (sepiaRed > 255) {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255) {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255) {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width/2.0); j++)
        {
            // Swap pixels
            int dest = width-j-1;

            int tempRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][dest].rgbtRed;
            image[i][dest].rgbtRed = tempRed;

            int tempGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][dest].rgbtGreen;
            image[i][dest].rgbtGreen = tempGreen;

            int tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][dest].rgbtBlue;
            image[i][dest].rgbtBlue = tempBlue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top line
            if (i == 0) {
                // top line + leftest
                if (j == 0) {
                    int avgRed = round((image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 4.0);
                    int avgGreen = round((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 4.0);
                    int avgBlue = round((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 4.0);
                    copy[i][j].rgbtRed = avgRed;
                    copy[i][j].rgbtGreen = avgGreen;
                    copy[i][j].rgbtBlue = avgBlue;
                }
                // top line + rightest
                else if (j == width-1) {
                    int avgRed = round((image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed) / 4.0);
                    int avgGreen = round((image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen) / 4.0);
                    int avgBlue = round((image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue) / 4.0);
                    copy[i][j].rgbtRed = avgRed;
                    copy[i][j].rgbtGreen = avgGreen;
                    copy[i][j].rgbtBlue = avgBlue;
                }
                // top line + middles
                else {
                    int avgRed = round((image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 6.0);
                    int avgGreen = round((image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 6.0);
                    int avgBlue = round((image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 6.0);
                    copy[i][j].rgbtRed = avgRed;
                    copy[i][j].rgbtGreen = avgGreen;
                    copy[i][j].rgbtBlue = avgBlue;
                }
            }
            // bottom line
            else if (i == height-1) {
                // bottom line + i=0
                if (j == 0) {
                    int avgRed = round((image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed) / 4.0);
                    int avgGreen = round((image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen) / 4.0);
                    int avgBlue = round((image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue) / 4.0);
                    copy[i][j].rgbtRed = avgRed;
                    copy[i][j].rgbtGreen = avgGreen;
                    copy[i][j].rgbtBlue = avgBlue;
                }
                // bottom line + i=width-1
                else if (j == width-1) {
                    int avgRed = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed) / 4.0);
                    int avgGreen = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen) / 4.0);
                    int avgBlue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue) / 4.0);
                    copy[i][j].rgbtRed = avgRed;
                    copy[i][j].rgbtGreen = avgGreen;
                    copy[i][j].rgbtBlue = avgBlue;
                }
                // bottom line + middles
                else {
                    int avgRed = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed) / 6.0);
                    int avgGreen = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen) / 6.0);
                    int avgBlue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue) / 6.0);
                    copy[i][j].rgbtRed = avgRed;
                    copy[i][j].rgbtGreen = avgGreen;
                    copy[i][j].rgbtBlue = avgBlue;
                }
            }
            // middle
            else {
                // middle, i=0
                if (j == 0) {
                    int avgRed = round((image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 6.0);
                    int avgGreen = round((image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 6.0);
                    int avgBlue = round((image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 6.0);
                    copy[i][j].rgbtRed = avgRed;
                    copy[i][j].rgbtGreen = avgGreen;
                    copy[i][j].rgbtBlue = avgBlue;
                }
                // middle, i=width-1
                else if (j == width-1) {
                    int avgRed = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed) / 6.0);
                    int avgGreen = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen) / 6.0);
                    int avgBlue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue) / 6.0);
                    copy[i][j].rgbtRed = avgRed;
                    copy[i][j].rgbtGreen = avgGreen;
                    copy[i][j].rgbtBlue = avgBlue;
                }
                 // middle, middle
                else {
                    int avgRed = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed+ image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed+ image[i+1][j+1].rgbtRed ) / 9.0);
                    int avgGreen = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen+ image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen+ image[i+1][j+1].rgbtGreen ) / 9.0);
                    int avgBlue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue+ image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue+ image[i+1][j+1].rgbtBlue ) / 9.0);
                    copy[i][j].rgbtRed = avgRed;
                    copy[i][j].rgbtGreen = avgGreen;
                    copy[i][j].rgbtBlue = avgBlue;
                }
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
}
