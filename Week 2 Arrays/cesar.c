#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: caesar <clave>\n");
        return 1;
    }

    char *endptr;
    long key = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0')
    {
        fprintf(stderr, "La clave debe ser un número entero.\n");
        return 1;
    }

    key = key % 26;
    if (key < 0) key += 26;

    char plaintext[4096];
    printf("plaintext: ");
    if (!fgets(plaintext, sizeof(plaintext), stdin)) return 1;
    plaintext[strcspn(plaintext, "\r\n")] = '\0';

    size_t len = strlen(plaintext);
    char *ciphertext = malloc(len + 1);
    if (!ciphertext) return 1;

    for (size_t i = 0; i < len; ++i)
    {
        unsigned char c = (unsigned char)plaintext[i];
        if (isupper(c))
        {
            ciphertext[i] = (char)(((c - 'A' + key) % 26) + 'A');
        }
        else if (islower(c))
        {
            ciphertext[i] = (char)(((c - 'a' + key) % 26) + 'a');
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';

    printf("ciphertext: %s\n", ciphertext);
    free(ciphertext);
    return 0;
}