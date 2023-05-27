#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < width; row++)
    {// looping through rows of pixels
        for (int column = 0; column < height; column++)
        {
            if(image[column][row].rgbtBlue == 0 && image[column][row].rgbtGreen == 0 && image[column][row].rgbtRed == 0) // checks if each pixel is black  
            {
                image[column][row].rgbtBlue = 255;
                image[column][row].rgbtGreen = 238;
                image[column][row].rgbtBlue = 151;

            }
            
        }
    }
    // looping through column of pixels
}
