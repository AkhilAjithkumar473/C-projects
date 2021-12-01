#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage : ./substitution key\n");
        return 1;
    }
    int length = strlen(argv[1]);
    if (length != 26)
    {
        printf("The key must have 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < length; i++)
{
    if(!isalpha (argv[1][i]))
    {
        printf("The key must contain only alphabetical characters.\n");
    }
}
    for (int i = 0; i < length; i++) // checks that there is no repeat characters
    {
        for (int j = 0; j < length; j++)
        {
            if (i != j)
            {
                if (tolower(argv[1][i]) == tolower(argv[1][j]))
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }

        }
    }
/////////////////////////////////
string s = get_string("Plaintext :");
int slength = strlen(s);
int shift;

printf("Ciphertext :");

for(int i = 0; i < slength; i++)
{
        if(isupper (s[i]))
        {
            shift = s[i] %65;
            s[i] = toupper(argv[1][shift]);
        }

    else if(islower (s[i]))
    {
        shift = s[i] %97;
        s[i] = tolower(argv[1][shift]);
    }
    printf("%c", s[i]);
}
printf("\n");
}