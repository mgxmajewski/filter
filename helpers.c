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
    
    // Declare variables to cumulate boxes all pixels RGB values
    double red_box;
    double green_box;
    double blue_box;
    
    // Decalre variable to get right divider to calculate avarage
    int avg_divider; // it will be different than 9 for corner(4) and edge(6)
    
    
    // Create set of nested loops to get each pixel of image which will become a center of a box
    
    // Loops through (horizontal) rows where row = 0 is the top row 
    for (int row = 0; row < height; row++)
    {
        // Loops through (vertical) columns where column = 0 is the first left column
        for (int column = 0; column < width; column++)
        {
            red_box = 0;
            green_box = 0;
            blue_box = 0;
            avg_divider =0;
            
            
            // Loops through (horizontal) rows - begins with -1 because we get preciding row
            for (int row_box = row - 1; row_box <= 1; row_box++)
            {
                // Loops through (vertical) box_col - begins with -1 because we get preciding column
                for (int column_box = column - 1; column_box <= 1; column_box++)
                {
                    // Adds condition to exclude outer pixels which are "forced" by 3x3 box loop 
                    if((row_box >= 0 && row_box <width) && (column_box >= 0 && column_box < height))
                    {
                        red_box += image[row_box][column_box].rgbtRed;
                        green_box += image[row_box][column_box].rgbtGreen;
                        blue_box += image[row_box][column_box].rgbtBlue;
                        avg_divider++;   
                    }
                }
            }
            
            red_box = round(red_box/(double)avg_divider);
            green_box = round(green_box/(double)avg_divider);
            blue_box = round(blue_box/(double)avg_divider);
            
            temp[row][column].rgbtRed = red_box;
            temp[row][column].rgbtGreen = green_box;
            temp[row][column].rgbtBlue = blue_box;
        }
    }
    
    // Loops through (horizontal) rows where row = 0 is the top row 
    for (int row = 0; row < height; row++)
    {
        // Loops through (vertical) columns where column = 0 is the first left column
        for (int column = 0; column < width; column++)
        {
            // Populate image array with "blur avaraged" new pixels
            image[row][column] = temp[row][column];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
