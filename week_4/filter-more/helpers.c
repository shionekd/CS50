submit50 cs50/problems/2024/x/filter/more#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Function prototypes
int sumPixel(int x, int y, int avgTotals[], double avgCount, int width, int height,
             RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            double doubleAvg =
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int avg = round(doubleAvg);
            // Update pixel values
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width / 2.0); j++)
        {
            // Swap pixels
            int dest = width - j - 1;

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
    // [R, G, B]
    int avgTotals[] = {0, 0, 0};
    double avgCount = 0.0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    avgCount = sumPixel(i + x, j + y, avgTotals, avgCount, width, height, image);
                }
            }
            copy[i][j].rgbtRed = round(avgTotals[0] / avgCount);
            copy[i][j].rgbtGreen = round(avgTotals[1] / avgCount);
            copy[i][j].rgbtBlue = round(avgTotals[2] / avgCount);
            avgTotals[0] = 0;
            avgTotals[1] = 0;
            avgTotals[2] = 0;
            avgCount = 0.0;
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

int sumPixel(int x, int y, int avgTotals[], double avgCount, int width, int height,
             RGBTRIPLE image[height][width])
{
    if (x >= 0 && x < height && y >= 0 && y < width)
    {
        avgCount++;

        avgTotals[0] += image[x][y].rgbtRed;
        avgTotals[1] += image[x][y].rgbtGreen;
        avgTotals[2] += image[x][y].rgbtBlue;
    }
    return avgCount;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // reset sums value
    int GxRedSum = 0;
    int GxGreenSum = 0;
    int GxBlueSum = 0;

    int GyRedSum = 0;
    int GyGreenSum = 0;
    int GyBlueSum = 0;

    int GxGyRedSum = 0;
    int GxGyGreenSum = 0;
    int GxGyBlueSum = 0;

    int aryX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int aryY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (i + x >= 0 && i + x < height && j + y >= 0 && j + y < width)
                    {
                        GxRedSum += image[i + x][j + y].rgbtRed * aryX[x + 1][y + 1];
                        GxGreenSum += image[i + x][j + y].rgbtGreen * aryX[x + 1][y + 1];
                        GxBlueSum += image[i + x][j + y].rgbtBlue * aryX[x + 1][y + 1];

                        GyRedSum += image[i + x][j + y].rgbtRed * aryY[x + 1][y + 1];
                        GyGreenSum += image[i + x][j + y].rgbtGreen * aryY[x + 1][y + 1];
                        GyBlueSum += image[i + x][j + y].rgbtBlue * aryY[x + 1][y + 1];
                    }
                }
            }

            GxGyRedSum = round(sqrt(GxRedSum * GxRedSum + GyRedSum * GyRedSum));
            if (GxGyRedSum > 255)
            {
                GxGyRedSum = 255;
            }
            copy[i][j].rgbtRed = GxGyRedSum;

            GxGyGreenSum = round(sqrt(GxGreenSum * GxGreenSum + GyGreenSum * GyGreenSum));
            if (GxGyGreenSum > 255)
            {
                GxGyGreenSum = 255;
            }
            copy[i][j].rgbtGreen = GxGyGreenSum;

            GxGyBlueSum = round(sqrt(GxBlueSum * GxBlueSum + GyBlueSum * GyBlueSum));
            if (GxGyBlueSum > 255)
            {
                GxGyBlueSum = 255;
            }
            copy[i][j].rgbtBlue = GxGyBlueSum;

            GxGyRedSum = 0.0;
            GxGyGreenSum = 0.0;
            GxGyBlueSum = 0.0;

            GxRedSum = 0.0;
            GxGreenSum = 0.0;
            GxBlueSum = 0.0;

            GyRedSum = 0.0;
            GyGreenSum = 0.0;
            GyBlueSum = 0.0;
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
