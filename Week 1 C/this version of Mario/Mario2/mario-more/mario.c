#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    for (int i = 0; i < h; i++)
    {
        // Espacios a la izquierda
        for (int s = 0; s < h - i - 1; s++)
        {
            printf(" ");
        }

        // Pirámide izquierda
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // Separación (2 espacios)
        printf("  ");

        // Pirámide derecha
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
