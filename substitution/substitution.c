#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int key_validation(string key);
string cipher(string key, string plaintext);
const char UPALPHA[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const char LOWALPHA[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};


int main(int argc, string argv[])
{
    int x = 0;

    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }
    string key = argv[1];

    if (key_validation(key) == 1)
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: %s\n", cipher(key, plaintext));
}

int key_validation(string key)
{
    if (strlen(key) == 0)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (strlen(key) < 26)
    {
        printf("Usage: ./substitution KEY.\n");
        return 1;
    }

    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters\n");
            return 1;
        }

        if (i < 25)
        {
            for (int j = i + 1; j < strlen(key); j++)
            {
                if (tolower(key[j]) == tolower(key[i]))
                {
                    printf("Key must not contain repeated characters\n");
                    return 1;
                }
            }
        }
    }
    return 0;
}

string cipher(string key, string plaintext)
{
    int j = 0;
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (islower(plaintext[i]))
        {
            for (j = 0; j < 26; j++)
            {
                if (LOWALPHA[j] == plaintext[i])
                {
                    break;
                }
            }
        }
        else
        {
            for (j = 0; j < 26; j++)
            {
                if (UPALPHA[j] == plaintext[i])
                {
                    break;
                }
            }
        }

        if (islower(plaintext[i]) && isalpha(plaintext[i]))
        {
            plaintext[i] = (tolower(key[j]));
        }
        else if (isalpha(plaintext[i]))
        {
            plaintext[i] = (toupper(key[j]));
        }
    }
    return plaintext;
}
