#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel by row then column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Find each RGB value and then average it
            int blue = image[h][w].rgbtBlue;
            int green = image[h][w].rgbtGreen;
            int red = image[h][w].rgbtRed;

            int final = round((blue + green + red) / 3.0);

            // Apply the average to every value for that pixel
            image[h][w].rgbtBlue = final;
            image[h][w].rgbtGreen = final;
            image[h][w].rgbtRed = final;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel by row then column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < round(width / 2); w++)
        {
            // Change the image based on the opposite
            RGBTRIPLE original = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = original;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];

    // Loop through every pixel by row then column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Copy the image to create an original file
            original[h][w] = image[h][w];
        }
    }
    // Loop through every pixel by row then column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float blue = 0;
            float green = 0;
            float red = 0;
            int num = 0;

            // Loop in a 3 x 3 grid of the chosen pixel
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    // Make sure that the pixel exists to do a calculation on
                    if (h + i >= 0 && h + i < height && w + j >= 0 && w + j < width)
                    {
                        blue += original[h + i][w + j].rgbtBlue;
                        green += original[h + i][w + j].rgbtGreen;
                        red += original[h + i][w + j].rgbtRed;
                        num += 1;
                    }
                }
            }
            // Calculate and apply the final values
            image[h][w].rgbtBlue = round(blue / num);
            image[h][w].rgbtGreen = round(green / num);
            image[h][w].rgbtRed = round(red / num);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];

    // Loop through every pixel by row then column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Copy the image to create an original file
            original[h][w] = image[h][w];
        }
    }
    // Loop through every pixel by row then column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int options[3] = {1, 2, 1};
            
            int blueX = 0;
            int greenX = 0;
            int redX = 0;
            
            int blueY = 0;
            int greenY = 0;
            int redY = 0;

            // Loop in a 3 x 3 grid of the chosen pixel
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    // Make sure that the pixel exists to do a calculation on
                    if (h + i >= 0 && h + i < height && w + j >= 0 && w + j < width)
                    {
                        blueX += j * options[i + 1] * original[h + i][w + j].rgbtBlue;
                        greenX += j * options[i + 1] * original[h + i][w + j].rgbtGreen;
                        redX += j * options[i + 1] * original[h + i][w + j].rgbtRed;
                        
                        blueY += i * options[j + 1] * original[h + i][w + j].rgbtBlue;
                        greenY += i * options[j + 1] * original[h + i][w + j].rgbtGreen;
                        redY += i * options[j + 1] * original[h + i][w + j].rgbtRed;
                    }
                }
            }
            // Calculate the final values
            int rgb[3];
            
            rgb[2] = round(sqrt(pow(blueX, 2) + pow(blueY, 2)));
            rgb[1] = round(sqrt(pow(greenX, 2) + pow(greenY, 2)));
            rgb[0] = round(sqrt(pow(redX, 2) + pow(redY, 2)));
            
            // Make sure none of the outputs are over 255
            for (int i = 0; i < 3; i++)
            {
                if (rgb[i] > 255)
                {
                    rgb[i] = 255;
                }
            }
            // Apply the final values
            image[h][w].rgbtBlue = rgb[2];
            image[h][w].rgbtGreen = rgb[1];
            image[h][w].rgbtRed = rgb[0];
        }
    }
    return;
}