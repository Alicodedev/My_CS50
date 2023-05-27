#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row = 0; row < width; row++) // loops through each row of the pixels
    {
        for(int col = 0; col < height; col++)// loops through each column of the pixels
        {
            int avg , total;
            avg = (image[col][row].rgbtBlue + image[col][row].rgbtGreen + image[col][row].rgbtRed) / 3; // calculates average

            total = round(avg); 

            image[col][row].rgbtBlue = image[col][row].rgbtGreen = image[col][row].rgbtRed = total; // redefines each rgb pixel to average

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


