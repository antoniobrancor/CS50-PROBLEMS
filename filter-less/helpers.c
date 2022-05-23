#include "helpers.h"
#include "math.h"
#include "string.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = sum;
            image[i][j].rgbtGreen = sum;
            image[i][j].rgbtRed = sum;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float originalBlue = image[i][j].rgbtBlue;
            float originalGreen = image[i][j].rgbtGreen;
            float originalRed = image[i][j].rgbtRed;

            double blue = 0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue;
            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(blue);
            }
            double green = 0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue;
            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(green);
            }
            double red = 0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue;
            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(red);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE aux;
        for (int j = 0; j < round(width/2); j++)
        {
        aux = image[i][j];
        image[i][j] = image[i][width - j - 1];
        image[i][width - j - 1] = aux;
        }
    }
    return;

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];
    int control[3][3];
    memset(control, 0, (sizeof (control[0][0])) * 3 * 3);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRed = 0;
            float sumBlue = 0;
            float sumGreen = 0;
            int pixelCount = 1;

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                printf("entrou aqui[%d][%d]\n",i - 1 ,j - 1);
                sumRed += original[i - 1][j - 1].rgbtRed;
                sumBlue += original[i - 1][j - 1].rgbtBlue;
                sumGreen += original[i - 1][j - 1].rgbtGreen;
                pixelCount++;
                //control[0][0] = 1;
            }
            if(i - 1 >= 0)
            {
                printf("entrou aqui[%d][%d]\n",i - 1,j);
                sumRed += original[i - 1][j].rgbtRed;
                sumBlue += original[i - 1][j].rgbtBlue;
                sumGreen += original[i - 1][j].rgbtGreen;
                pixelCount++;
                //control[0][1] = 1;
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                printf("entrou aqui[%d][%d]\n",i - 1,j + 1);
                sumRed += original[i - 1][j + 1].rgbtRed;
                sumBlue += original[i - 1][j + 1].rgbtBlue;
                sumGreen += original[i - 1][j + 1].rgbtGreen;
                pixelCount++;
                //control[0][2] = 1;
            }
            if (j + 1 < width)
            {
                printf("entrou aqui[%d][%d]\n",i ,j + 1);
                sumRed += original[i][j + 1].rgbtRed;
                sumBlue += original[i][j + 1].rgbtBlue;
                sumGreen += original[i][j + 1].rgbtGreen;
                pixelCount++;
                //control[1][2] = 1;
            }
            if (i + 1 < height && j + 1 < width)
            {
                printf("entrou aqui[%d][%d]\n",i + 1,j + 1);
                sumRed += original[i + 1][j + 1].rgbtRed;
                sumBlue += original[i + 1][j + 1].rgbtBlue;
                sumGreen += original[i + 1][j + 1].rgbtGreen;
                pixelCount++;
                //control[2][2] = 1;
            }
            if (i + 1 < height)
            {
                printf("entrou aqui[%d][%d]\n",i + 1,j);
                sumRed += original[i + 1][j].rgbtRed;
                sumBlue += original[i + 1][j].rgbtBlue;
                sumGreen += original[i + 1][j].rgbtGreen;
                pixelCount++;
                //control[2][1] = 1;
            }
            if (i + 1 < height && j - 1 >= 0)
            {
                printf("entrou aqui[%d][%d]\n",i + 1,j - 1);
                sumRed += original[i + 1][j - 1].rgbtRed;
                sumBlue += original[i + 1][j - 1].rgbtBlue;
                sumGreen += original[i + 1][j - 1].rgbtGreen;
                pixelCount++;
                //control[2][0] = 1;
            }
            if (j - 1 >= 0)
            {
                printf("entrou aqui[%d][%d]\n",i ,j - 1);
                sumRed += original[i][j - 1].rgbtRed;
                sumBlue += original[i][j - 1].rgbtBlue;
                sumGreen += original[i][j - 1].rgbtGreen;
                pixelCount++;
                //control[1][0] = 1;
            }
            sumRed += original[i][j].rgbtRed;
            sumBlue += original[i][j].rgbtBlue;
            sumGreen += original[i][j].rgbtGreen;
            printf("-----------------------------------------\n");
            if (pixelCount > 1)
            {
                image[i][j].rgbtRed = round(sumRed / (float)pixelCount);
                image[i][j].rgbtBlue = round(sumBlue / (float)pixelCount);
                image[i][j].rgbtGreen = round(sumGreen / (float)pixelCount);
            }
        }
    }
    return;
}
