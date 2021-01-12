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
            
            int average_rgb = round(((float)red + (float)green + (float)blue) / rgb_struct_length);
            
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
        for (int j = 0; j < width / 2; j++)
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
    // Declare array which will keep temporary copy of 
    RGBTRIPLE temp[height][width];
    
    // Declare variables to cumulate all pixels RGB values of the 3x3 blur box
    float red_box, green_box, blue_box;
    
    // Decalre variable to set divider to calculate avarage
    float avg_divider; // it will be different than 9 for corner(4) and edge(6) pixels
    
    
    // Create set of nested loops to get each pixel of image which will become a center of a box
    
    // Loops through (horizontal) rows where row = 0 is the top row 
    for (int row = 0; row < height; row++)
    {
        // Loops through (vertical) columns where column = 0 is the first left column
        for (int column = 0; column < width; column++)
        {
            // Reset pixel values
            red_box = 0;
            green_box = 0;
            blue_box = 0;
            avg_divider = 0;
            
            // Loops through (horizontal) rows - begins with -1 because box include preciding row
            for (int row_box = row - 1; row_box <= row + 1 ; row_box++)
            {
                // Loops through (vertical) box_col - begins with -1 because box include preciding row
                for (int column_box = column - 1; column_box <= column + 1; column_box++)
                {
                    // Adds condition to exclude pixels outside image which are "forced" by 3x3 box 
                    if ((row_box >= 0 && row_box < width) && (column_box >= 0 && column_box < height))
                    {
                        // Cumulates pixel RGB values (only those included in image)
                        red_box += image[row_box][column_box].rgbtRed;
                        green_box += image[row_box][column_box].rgbtGreen;
                        blue_box += image[row_box][column_box].rgbtBlue;
                        avg_divider++;   
                    }
                }
            }
            // Asign calculated RGB avarages to the blur boxes center pixel
            temp[row][column].rgbtRed = round(red_box / avg_divider);
            temp[row][column].rgbtGreen = round(green_box / avg_divider);
            temp[row][column].rgbtBlue = round(blue_box / avg_divider);
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
    // Declare 2 arrays which will keep temporary copy of 
    RGBTRIPLE tempGx[height][width];
    RGBTRIPLE tempGy[height][width];
    
    // Declare variables to calculate Gx and Gy pixels RGB values of the 3x3 blur box
    float red_Gx, green_Gx, blue_Gx, red_Gy, green_Gy, blue_Gy;
    
    // Create set of nested loops to get each pixel of image which will become a center of a box
    
    // Loops through (horizontal) rows where row = 0 is the top row 
    for (int row = 0; row < height; row++)
    {
        // Loops through (vertical) columns where column = 0 is the first left column
        for (int column = 0; column < width; column++)
        {
            // Reset Gx and Gy values for each pixel
            red_Gx = 0;
            green_Gx = 0;
            blue_Gx = 0;
            red_Gy = 0;
            green_Gy = 0;
            blue_Gy = 0;
            
            // Loops through (horizontal) rows - begins with -1 because matrix include preciding row
            for (int row_convolute = row - 1; row_convolute <= row + 1 ; row_convolute++)
            {
                // Loops through (vertical) box_col - begins with -1 because matrix include preciding row
                for (int column_convolute = column - 1; column_convolute <= column + 1; column_convolute++)
                {
                    // Adds condition to exclude pixels outside image which are "forced" by 3x3 box 
                    if ((row_convolute >= 0 && row_convolute < width) && (column_convolute >= 0 && column_convolute < height))
                    {
                        // Here we gonna multiply two matrixes: convolution Gx matrix with pixel RGB values matrix
                        
                        // Here we gonna multiply two matrixes: convolution Gy matrix with pixel RGB values matrix
                    }
                    else 
                    {
                        continue;
                    }
                }
            }        
        }
    }
    return;
}
