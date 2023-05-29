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
    for(int row = 0; row < width; row++) // loops through each row of the pixels
    {
        for(int col = 0; col < height; col++)// loops through each column of the pixels
        {
            int sepiaRed, sepiaGreen, sepiaBlue; // each sepiaRGB variable for storing the correct color mix

            sepiaRed = (.393 * image[col][row].rgbtRed) + (.769 * image[col][row].rgbtGreen) + (.189 * image[col][row].rgbtBlue);
            sepiaGreen = (.349 * image[col][row].rgbtRed) + (.686 * image[col][row].rgbtGreen) + (.168 * image[col][row].rgbtBlue);
            sepiaBlue = (.272 * image[col][row].rgbtRed) + (.534 * image[col][row].rgbtGreen) + (.131 * image[col][row].rgbtBlue);

            if( sepiaRed <= 255 && sepiaBlue <= 255 && sepiaGreen <= 255){ // keep pixels within color range of 0 255

                image[col][row].rgbtRed = sepiaRed;
                image[col][row].rgbtBlue = sepiaBlue;
                image[col][row].rgbtGreen = sepiaGreen;
                }
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


