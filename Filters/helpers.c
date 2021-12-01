#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
    {
        float RGBgray;

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                //Average the colour to get grayscale
                RGBgray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.000);

                //Assigning each pixel the grayscale filter
                image[i][j].rgbtBlue = RGBgray;
                  image[i][j].rgbtGreen = RGBgray;
                    image[i][j].rgbtRed = RGBgray;

            }
        }
    }
//Restricting the overflow of bits
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Making a buffer to store some temporary values
    int buffer[3];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            //Storing values in a buffer temporarily
            buffer[0] = image[i][j].rgbtBlue;
            buffer[1] = image[i][j].rgbtGreen;
            buffer[2] = image[i][j].rgbtRed;

            //Swapping the left side of the image with right side pixels
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = buffer[0];
            image[i][width - j - 1].rgbtGreen = buffer[1];
            image[i][width - j - 1].rgbtRed = buffer[2];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_red;
            float sum_blue;
            float sum_green;
            int counter;
            sum_red = sum_blue = sum_green = counter = 0;
     // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    sum_red += temp[i + k][j + l].rgbtRed;
                    sum_blue += temp[i + k][j + l].rgbtBlue;
                    sum_green += temp[i + k][j + l].rgbtGreen;
                    counter++;
                }
            }
            // Get average and blur image
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Create temporary array
    RGBTRIPLE temp[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    //Initialise Sobel Operator
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float Gx_red;
            float Gx_blue;
            float Gx_green;
            float Gy_red;
            float Gy_blue;
            float Gy_green;

            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;
            for(int k = -1; k < 2; k++)
            {
                for(int l = -1; l < 2; l++)
                {
                    //Check if pixels is outside rows
                    if(i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    //Check if pixels is outside columns
                    if(j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    //Otherwise add to sums
                    Gx_red += temp[k + i][j + l].rgbtRed*Gx[k + 1][l + 1];
                    Gx_blue += temp[k + i][j + l].rgbtBlue*Gx[k + 1][l + 1];
                    Gx_green += temp[k + i][j + l].rgbtGreen*Gx[k + 1][l + 1];
                    Gy_red += temp[k + i][j + l].rgbtRed*Gy[k + 1][l + 1];
                    Gy_blue += temp[k + i][j + l].rgbtBlue*Gy[k + 1][l + 1];
                    Gy_green += temp[k + i][j + l].rgbtGreen*Gy[k + 1][l + 1];


                }
            }
                   // Calculate Sobel operator
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}