#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = (float)image[i][j].rgbtRed;
            float green = (float)image[i][j].rgbtGreen;
            float blue = (float)image[i][j].rgbtBlue;
            
            int rgb_struct_length = 3;
            
            int average_rgb = ceil((red+green+blue)/rgb_struct_length);
            
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average_rgb;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
