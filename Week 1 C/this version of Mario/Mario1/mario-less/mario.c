#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h <= 0);

    for (int row = 1; row <= h; row++)
    {
        for (int s = 0; s < h - row; s++)
        {
            printf(" ");
        }

        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        }

        printf("\n");
    }
}
