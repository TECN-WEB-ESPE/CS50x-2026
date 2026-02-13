#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // verificar argumentos
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // abrir memoria
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[512];

    FILE *img = NULL;
    int count = 0;
    char filename[8];

    // leer bloques
    while (fread(buffer, 1, 512, card) == 512)
    {
        // verificar header JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // cerrar archivo anterior
            if (img != NULL)
            {
                fclose(img);
            }

            // crear nombre archivo
            sprintf(filename, "%03i.jpg", count);

            // abrir nuevo archivo
            img = fopen(filename, "w");
            count++;
        }

        // si ya estamos escribiendo una imagen
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // cerrar todo
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
}
