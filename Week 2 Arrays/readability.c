#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(const char *text)
{
    int count = 0;
    for (size_t i = 0; text[i] != '\0'; ++i)
    {
        if (isalpha((unsigned char)text[i]))
            count++;
    }
    return count;
}

int count_words(const char *text)
{
    int count = 0;
    size_t len = strlen(text);
    if (len == 0) return 0;
    for (size_t i = 0; text[i] != '\0'; ++i)
    {
        if (text[i] == ' ')
            count++;
    }
    return count + 1;
}

int count_sentences(const char *text)
{
    int count = 0;
    for (size_t i = 0; text[i] != '\0'; ++i)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            count++;
    }
    return count;
}

int main(void)
{
    char text[4096];

    printf("Texto: ");
    if (!fgets(text, sizeof(text), stdin)) return 1;
    text[strcspn(text, "\r\n")] = '\0';

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    if (words == 0)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    double L = (double)letters / words * 100.0;
    double S = (double)sentences / words * 100.0;

    double index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int)round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

    return 0;
}
