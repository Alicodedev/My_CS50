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
    for(int row = 0; row < height; row++) // loops through each row of the pixels
    {
        for(int col = 0; col < width / 2; col++)// loops through each column to it's half way mark
        {   
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width - (col + 1)]; // swap each pixel of width by width - (column + 1)
            image[row][width - (col + 1 )] = temp;
           
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int x = 0; x < height; x++)
    {
        for(int y = 0; y < width; y++)
        {
            temp[x][y] = image[x][y];

        }
    }

     for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
           int sum_Red, sum_Blue, sum_Green;
           sum_Red = sum_Blue = sum_Green = 0;
           float counter = 0.00;

            for(int x = -1; x < 2; x++)
            {
                for(int y = -1; y < 2; y++)
                {
                    int curr_x = row + x;
                    int curr_y = col + y;

                    if (curr_x < 0 || curr_x > (height + 1) || curr_y < 0 || curr_y > (width - 1) )
                    {
                        continue;
                    }

                    sum_Red += image[curr_x][curr_y]. rgbtRed;
                    sum_Blue += image[curr_x][curr_y].rgbtBlue;
                    sum_Green += image[curr_x][curr_y].rgbtGreen;

                    counter++;

                }

                temp[row][col].rgbtRed = round(sum_Red / counter);
                temp[row][col].rgbtBlue = round(sum_Blue / counter);
                temp[row][col].rgbtGreen = round(sum_Green / counter);
            }
        }
    }

    for (int x = 0; x < height; x++)
    {
        for(int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = temp[x][y].rgbtRed;
            image[x][y].rgbtGreen = temp[x][y].rgbtGreen;
            image[x][y].rgbtBlue= temp[x][y].rgbtBlue;
        }
    }
    return;
}
