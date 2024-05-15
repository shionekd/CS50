#import <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool length_check(string s);
bool letter_check(string s);
bool repeated_check(string s);
void rotate(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (!length_check(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (!letter_check(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (!repeated_check(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        string plaintext = get_string("plaintext: ");
        rotate(plaintext, argv[1]);
    }
}

bool length_check(string key)
{
    int length = strlen(key);
    if (length == 26)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool letter_check(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122)
        {
            return false;
        }
    }
    return true;
}

bool repeated_check(string key)
{
    string check_ary[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 26; i++)
    {
        key[i] = toupper(key[i]);
        if (check_ary[key[i] - 65])
        {
            return false;
        }
        else
        {
            check_ary[key[i] - 65] += 1;
        }
    }
    return true;
}

void rotate(string plaintext, string key)
{
    for (int j = 0; j < 26; j++)
    {
        key[j] = tolower(key[j]);
        // printf("tolower: %c", key[j]);
        // printf("\n");
    }
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char letter = plaintext[i];
        int offset = 0;

        if (letter > 64 && letter < 91)
        {
            offset = 'A';
            printf("%c", toupper(key[letter - offset]));
        }
        else if (letter > 96 && letter < 123)
        {
            offset = 'a';
            printf("%c", key[letter - offset]);
        }
        else
        {
            printf("%c", letter);
        }
    }
    printf("\n");
}
