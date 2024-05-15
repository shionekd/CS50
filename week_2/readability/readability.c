#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int length = strlen(text);
    float Count_words = 0;
    float Count_sentences = 0;
    float Count_letters = 0;
    if (length > 0)
    {
        Count_words++;
        for (int i = 0; i < length; i++)
        {
            if (text[i] == 32)
            {
                Count_words++;
            }
            else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
            {
                Count_sentences++;
            }
            else if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
            {
                Count_letters++;
            }
        }
    }

    // Compute the Coleman-Liau index
    float L = Count_letters / Count_words * 100;
    float S = Count_sentences / Count_words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print the grade level
    if (index < 0)
    {
        printf("Grade: Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade: Grade 16+\n");
    }
    else
    {
        printf("Grade %i", index);
        printf("\n");
    }
}
