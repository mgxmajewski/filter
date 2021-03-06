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

    // Create set of nested loops to get each pixel of image which will become a center of a box

    // Loops through (horizontal) rows where row = 0 is the top row
    for (int row = 0; row < height; row++)
    {
        // Loops through (vertical) columns where column = 0 is the first left column
        for (int col = 0; col < width; col++)
        {
            
            // Declare variables to cumulate all pixels RGB values of the 3x3 blur box
            float red_box, green_box, blue_box;

            // Decalre variable to set divider to calculate avarage
            int avg_divider = 0; // it will be different than 9 for corner(4) and edge(6) pixels
            
            // Reset pixel values
            red_box = 0;
            green_box = 0;
            blue_box = 0;
            
            int row_box[3] = {row - 1, row, row + 1};
            int col_box[3] = {col - 1, col, col + 1};

            // Loops through (horizontal) rows - begins with -1 because box include preciding row
            for (int x = 0; x <= 2 ; x++)
            {
                // Loops through (vertical) box_col - begins with -1 because box include preciding row
                for (int y = 0; y <= 2; y++)
                {
                    // Delare analized pixels position relative to box
                    int x_box = row_box[x];
                    int y_box = col_box[y];
                   
                    // Adds condition to exclude pixels outside image which are "forced" by 3x3 box
                    if ((x_box >= 0 && x_box < height) && (y_box >= 0 && y_box < width))
                    {
                        RGBTRIPLE pixel = image[x_box][y_box];
                        // Cumulates pixel RGB values (only those included in image)
                        red_box += pixel.rgbtRed;
                        green_box += pixel.rgbtGreen;
                        blue_box += pixel.rgbtBlue;
                        avg_divider++;
                    }
                }
            }
            // Asign calculated RGB avarages to the blur boxes center pixel
            int red_avg = round(red_box / avg_divider);
            int green_avg = round(green_box / avg_divider);
            int blue_avg = round(blue_box / avg_divider);
            
            
            temp[row][col].rgbtRed = red_avg;
            temp[row][col].rgbtGreen = green_avg;
            temp[row][col].rgbtBlue = blue_avg;
        }
    }

    // Loops through (horizontal) rows where row = 0 is the top row
    for (int row = 0; row < height; row++)
    {
        // Loops through (vertical) columns where column = 0 is the first left column
        for (int col = 0; col < width; col++)
        {
            // Populate image array with "blur avaraged" new pixels
            image[row][col] = temp[row][col];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare 2 arrays which will keep temporary copy of
    RGBTRIPLE tempG[height][width];

    // Declare convolutional matrixes (Sobel–Feldman operator)
    int gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Create set of nested loops to get each pixel of image which will become a center of a box

    // Loops through (horizontal) rows where row = 0 is the top row
    for (int row = 0; row < height; row++)
    {
        // Loops through (vertical) columns where column = 0 is the first left column
        for (int col = 0; col < width; col++)
        {
            // Create array describing 'boxes' used for calculations 
            int row_box[] = {row - 1, row, row + 1};
            int col_box[] = {col - 1, col, col + 1};
            
            // Declare variables to calculate Gx and Gy pixels RGB values of the 3x3 blur box
            int red_Gx, green_Gx, blue_Gx, red_Gy, green_Gy, blue_Gy;

            // Reset Gx and Gy values for each pixel
            red_Gx = 0;
            green_Gx = 0;
            blue_Gx = 0;
            red_Gy = 0;
            green_Gy = 0;
            blue_Gy = 0;

            // Loops through (horizontal) rows - begins with -1 because matrix include preciding row
            for (int x = 0; x <= 2 ; x++)
            {
                // Loops through (vertical) box_col - begins with -1 because matrix include preciding row
                for (int y = 0; y <= 2; y++)
                {
                    // Declare analized pixels position relative to box
                    int x_box = row_box[x];
                    int y_box = col_box[y];
                    // Adds condition to exclude pixels outside image which are "forced" by 3x3 box
                    if ((x_box >= 0 && x_box < height) && (y_box >= 0 && y_box < width))
                    {
                        // Multiply two matrixes: convolution Gx matrix with pixel RGB values matrix
                        red_Gx += image[x_box][y_box].rgbtRed * gx [x][y];
                        green_Gx += image[x_box][y_box].rgbtGreen * gx [x][y];
                        blue_Gx += image[x_box][y_box].rgbtBlue * gx [x][y];

                        // Multiply two matrixes: convolution Gy matrix with pixel RGB values matrix
                        red_Gy += image[x_box][y_box].rgbtRed * gy [x][y];
                        green_Gy += image[x_box][y_box].rgbtGreen * gy [x][y];
                        blue_Gy += image[x_box][y_box].rgbtBlue * gy [x][y];
                    }
                }
            }
            
            // Calculate G which is squared root of sum of squared Gx and Gy
            int red_edge = round(sqrt(red_Gx * red_Gx + red_Gy * red_Gy));
            int green_edge = round(sqrt(green_Gx * green_Gx + green_Gy * green_Gy));
            int blue_edge = round(sqrt(blue_Gx * blue_Gx + blue_Gy * blue_Gy));
            
            
            // Cap RGB avalues up to 255 using turneries
            tempG[row][col].rgbtRed = red_edge > 255 ? 255 : red_edge;
            tempG[row][col].rgbtGreen = green_edge > 255 ? 255 : green_edge;
            tempG[row][col].rgbtBlue = blue_edge > 255 ? 255 : blue_edge;
            
        }
    }
    
    // Loops through (horizontal) rows where row = 0 is the top row
    for (int row = 0; row < height; row++)
    {
        // Loops through (vertical) columns where column = 0 is the first left column
        for (int col = 0; col < width; col++)
        {
            // Populate image array with "blur avaraged" new pixels
            image[row][col] = tempG[row][col];
        }
    }
    return;
}
