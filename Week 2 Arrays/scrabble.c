#include <stdio.h>
#include <ctype.h>
#include <string.h>

static int POINTS[26] = {
    1,  // A
    3,  // B
    3,  // C
    2,  // D
    1,  // E
    4,  // F
    2,  // G
    4,  // H
    1,  // I
    8,  // J
    5,  // K
    1,  // L
    3,  // M
    1,  // N
    1,  // O
    3,  // P
    10, // Q
    1,  // R
    1,  // S
    1,  // T
    1,  // U
    4,  // V
    4,  // W
    8,  // X
    4,  // Y
    10  // Z
};

int compute_score(const char *word)
{
    int score = 0;
    for (size_t i = 0; word[i] != '\0'; ++i)
    {
        unsigned char uc = (unsigned char)word[i];
        char c = toupper(uc);
        if (c >= 'A' && c <= 'Z')
        {
            score += POINTS[c - 'A'];
        }
    }
    return score;
}

int main(void)
{
    char word1[1024];
    char word2[1024];

    printf("Jugador 1: ");
    if (!fgets(word1, sizeof(word1), stdin)) return 1;
    word1[strcspn(word1, "\r\n")] = '\0';

    printf("Jugador 2: ");
    if (!fgets(word2, sizeof(word2), stdin)) return 1;
    word2[strcspn(word2, "\r\n")] = '\0';

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Jugador 1 gana!\n");
    }
    else if (score2 > score1)
    {
        printf("Jugador 2 gana!\n");
    }
    else
    {
        printf("Empate!\n");
    }

    return 0;
}
