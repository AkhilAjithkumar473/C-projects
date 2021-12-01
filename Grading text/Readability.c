#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int main(void)
{
    string text = get_string("Text: \n");
    int countletters = 0, countwords = 0, countsentences = 0;
    if (isalpha(text[0]))
    {
        countwords++;
    }
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            countletters++;
        }
        if ((isspace(text[i]) || (text[i] == '"')) && isalpha(text[i + 1]))
        {
            countwords++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            countsentences++;
        }

    }
    float L = (float)countletters / (float)countwords * 100, S = (float)countsentences / (float)countwords * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("%f\n", index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}