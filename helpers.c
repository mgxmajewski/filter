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
    // Decalre array which will keep temporary copy of 
    RGBTRIPLE temp[height][width];
    
    
    // Create set of nested loops to get each pixel of image which will become a center of a box
    
    // Loops through (horizontal) rows where i = 0 is the top row 
    for (int row = 0; row < height; row++)
    {
        // Loops through (vertical) columns where j = 0 is the first left column
        for (int column = 0; column < width; column++)
        {
            // Declare variables to cumulate boxes all pixels RGB values
            int red_box, blue_box, green_box = 0;
            
            // Decalre variable to get right divider to calculate avarage
            int avg_divider = 0; // it will be different than 9 for corner(4) and edge(6)
            
            // Loops through (horizontal) rows - begins with -1 because we get preciding pixels
            for (int row_box = row - 1; row_box <= 1; row_box++)
            {
                for (int column_box = column - 1; column_box <= 1; column_box++)
                {
                    continue;
                }
            }
            // Loops through (vertical) box_col
            
            
            // Populate image array with "blur avaraged" new pixels
            temp[row][column] = image[row][column];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
