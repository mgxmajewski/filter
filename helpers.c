#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            
            int rgb_struct_length = 3;
            
            int average_rgb = round(((float)red+(float)green+(float)blue)/rgb_struct_length);
            
            image[i][j].rgbtRed = average_rgb;
            image[i][j].rgbtGreen = average_rgb;
            image[i][j].rgbtBlue = average_rgb;
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    
    // Loops through (horizontal) rows where i = 0 is the top row 
    for (int i = 0; i < height; i++)
    {
        // Loops through (vertical) columns where j = 0 is the first left column
        for (int j = 0; j < width; j++)
        {
            
            // Populates image array with "blur avaraged" new pixels
            temp[i][j] = image[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
