#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int promedio = round(
                (image[i][j].rgbtRed +
                 image[i][j].rgbtGreen +
                 image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = promedio;
            image[i][j].rgbtGreen = promedio;
            image[i][j].rgbtBlue = promedio;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // limitar a 255
            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // guardar temporal
            RGBTRIPLE temp = image[i][j];

            // intercambiar
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}


#include <math.h>

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copia temporal
    RGBTRIPLE copy[height][width];

    // recorrer cada pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // revisar vecinos 3x3
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int new_i = i + di;
                    int new_j = j + dj;

                    // verificar limites
                    if (new_i >= 0 && new_i < height &&
                        new_j >= 0 && new_j < width)
                    {
                        sumRed += image[new_i][new_j].rgbtRed;
                        sumGreen += image[new_i][new_j].rgbtGreen;
                        sumBlue += image[new_i][new_j].rgbtBlue;
                        count++;
                    }
                }
            }

            // guardar promedio en copia
            copy[i][j].rgbtRed = round((float) sumRed / count);
            copy[i][j].rgbtGreen = round((float) sumGreen / count);
            copy[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }

    // copiar de vuelta a la imagen original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
