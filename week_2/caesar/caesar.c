#import <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
string rotate(string c, int k);
void rotate2(string c, int k);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Make sure every character in argv[1] is a digit
    else if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int num = atoi("s");
        // Prompt user for plaintext
        string plaintext = get_string("plaintext: ");

        // For each character in the plaintext:
        // Rotate the character if it's a letter
        int k = atoi(argv[1]);

        rotate2(plaintext, k);
        // string ciphertext = rotate(plaintext, k);

        // printf("ciphertext: %s", ciphertext);
        // printf("\n");
    }
}

bool only_digits(string s)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(s[i]))
        // if (s[i] < 0 || s[i] > 9)
        {
            return false;
        }
    }
    return true;
}

string rotate(string plaintext, int k)
{
    int cnt = strlen(plaintext);
    string ciphertext = plaintext;
    for (int i = 0; i < cnt; i++)
    {
        if ((plaintext[i] > 64 && plaintext[i] < 91) || (plaintext[i] > 96 && plaintext[i] < 123))
        {
            int num = k % 26;
            int plaintextNum = plaintext[i] + num;
            if (((plaintext[i] > 64 && plaintext[i] < 91) && plaintextNum > 90) ||
                ((plaintext[i] > 96 && plaintext[i] < 123) && plaintextNum > 122))
            {
                ciphertext[i] = plaintextNum - 26;
            }
            else
            {
                ciphertext[i] = plaintextNum;
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    return ciphertext;
}

void rotate2(string plaintext, int k)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char letter = plaintext[i];
v
        if (letter > 64 && letter < 91)
        {
            offset = 'A';
        }
        else if (letter > 96 && letter < 123)
        {
            offset = 'a';
        }

        printf("%c", ((letter - offset) + k) % 26 + offset);
    }
    printf("\n");
}
