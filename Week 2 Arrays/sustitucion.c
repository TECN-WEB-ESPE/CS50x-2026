#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_valid_key(const char *key)
{
    if (strlen(key) != 26) return false;
    bool seen[26] = { false };
    for (size_t i = 0; key[i] != '\0'; ++i)
    {
        char c = toupper((unsigned char)key[i]);
        if (c < 'A' || c > 'Z') return false;
        int idx = c - 'A';
        if (seen[idx]) return false;
        seen[idx] = true;
    }
    return true;
}

char *encrypt(const char *text, const char *key)
{
    size_t len = strlen(text);
    char *out = malloc(len + 1);
    if (!out) return NULL;

    char upper_key[26];
    for (int i = 0; i < 26; ++i) upper_key[i] = toupper((unsigned char)key[i]);

    for (size_t i = 0; i < len; ++i)
    {
        unsigned char c = (unsigned char)text[i];
        if (isupper(c))
        {
            out[i] = upper_key[c - 'A'];
        }
        else if (islower(c))
        {
            out[i] = tolower(upper_key[c - 'a']);
        }
        else
        {
            out[i] = text[i];
        }
    }
    out[len] = '\0';
    return out;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Uso: substitution <clave>\n");
        return 1;
    }

    char *key = argv[1];
    if (!is_valid_key(key))
    {
        fprintf(stderr, "La clave debe contener 26 letras únicas.\n");
        return 1;
    }

    char plaintext[4096];
    printf("plaintext: ");
    if (!fgets(plaintext, sizeof(plaintext), stdin)) return 1;
    plaintext[strcspn(plaintext, "\r\n")] = '\0';

    char *ciphertext = encrypt(plaintext, key);
    if (!ciphertext) return 1;

    printf("ciphertext: %s\n", ciphertext);
    free(ciphertext);
    return 0;
}