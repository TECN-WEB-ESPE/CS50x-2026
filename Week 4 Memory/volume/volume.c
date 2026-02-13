// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // Crear buffer para header
    uint8_t header[HEADER_SIZE];

    // Leer header del archivo input
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);

    // Escribir header al archivo output
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);


    // TODO: Read samples from input file and write updated data to output file
    // Variable para guardar cada sample (2 bytes)
    int16_t sample;

    // Leer samples hasta el final del archivo
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        // Escalar volumen
        sample = sample * factor;

        // Escribir nuevo sample
        fwrite(&sample, sizeof(int16_t), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);
}
