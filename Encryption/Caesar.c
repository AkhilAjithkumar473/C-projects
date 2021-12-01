#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])

{
    //Check whether the key is decimal or not
    if (argc == 2 && isdigit(*argv[1]))
 {
  //Get the caesar key with atoi
        int k = atoi(argv[1]);
        //Get text
        string s = get_string("Plaintext:");
        //Print ciphertext
        printf("ciphertext:");

        //Iterate through each character of the Plaintext
        for(int i = 0, n = strlen(s); i < n; i++)
        {
            //Checking if it is lowercase
            if(s[i] >= 'a' && s[i] <= 'z')
            {
                printf("%c", (((s[i] - 'a') + k) %26) + 'a');
            }
            //Checking if it is uppercase
            else if(s[i] >= 'A' && s[i] <= 'Z')
            {
                printf("%c", (((s[i] - 'A') + k) %26) + 'A');
            }
            //Checking if it is neither
            else
            {
                printf("%c", s[i]);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
