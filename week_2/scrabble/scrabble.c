#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculation(string answer);

int main(void)
{
    string answer0 = get_string("Player1: ");
    string answer1 = get_string("Player2: ");

    int total = calculation(answer0);
    int total1 = calculation(answer1);

    if (total == total1)
    {
        printf("Tie!\n");
    }
    else if (total > total1)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int calculation(string answer)
{
    // Scrabble points array
    int array[26];
    array[0] = 1;   // A
    array[1] = 3;   // B
    array[2] = 3;   // C
    array[3] = 2;   // D
    array[4] = 1;   // E
    array[5] = 4;   // F
    array[6] = 2;   // G
    array[7] = 4;   // H
    array[8] = 1;   // I
    array[9] = 8;   // J
    array[10] = 5;  // K
    array[11] = 1;  // L
    array[12] = 3;  // M
    array[13] = 1;  // N
    array[14] = 1;  // O
    array[15] = 3;  // P
    array[16] = 10; // Q
    array[17] = 1;  // R
    array[18] = 1;  // S
    array[19] = 1;  // T
    array[20] = 1;  // U
    array[21] = 4;  // V
    array[22] = 4;  // W
    array[23] = 8;  // X
    array[24] = 4;  //  Y
    array[25] = 10; // Z

    int length = strlen(answer);
    int total = 0;
    int point = 0;
    for (int i = 0; i < length; i++)
    {
        if (answer[i] < 65 || (answer[i] > 90 && answer[i] < 97) || answer[i] > 122)
        {
            point = 0;
        }
        // else if (answer[i] >= 97 && answer[i] <= 122)
        // {
        //     point = array[answer[i] - 97];
        // }
        // else
        // {
        //     point = array[answer[i] - 65];
        // }
        else
        {
            point = array[toupper(answer[i]) - 65];
        }
        total += point;
    }
    return total;
}

// Another way - no loop

// int main(void)
// {
//     string answer0 = get_string("Player1: ");
//     string answer1 = get_string("Player2: ");

//     Scrabble points array
//     int array[26];
//     array[0] = 1; // A
//     array[1] = 3; // B
//     array[2] = 3; // C
//     array[3] = 2; // D
//     array[4] = 1; // E
//     array[5] = 4; // F
//     array[6] = 2; // G
//     array[7] = 4; // H
//     array[8] = 1; // I
//     array[9] = 8; // J
//     array[10] = 5; // K
//     array[11] = 1; // L
//     array[12] = 3; // M
//     array[13] = 1; // N
//     array[14] = 1; // O
//     array[15] = 3; // P
//     array[16] = 10; // Q
//     array[17] = 1; // R
//     array[18] = 1; // S
//     array[19] = 1; // T
//     array[20] = 1; // U
//     array[21] = 4; // V
//     array[22] = 4; // W
//     array[23] = 8; // X
//     array[24] = 4; //  Y
//     array[25] = 10; // Z

//     Answer1 points
//     int length = strlen(answer0);
//     int total = 0;
//     int point0 = 0;
//     for (int i = 0; i < length; i++)
//     {
//         if (answer0[i] >= 97 && answer0[i] <= 122)
//         {
//             point0 = array[answer0[i] - 97];
//             //printf("%i\n", answer0[i]);
//             //printf("%i\n", point0);
//         }
//         else
//         {
//             point0 = array[answer0[i] - 65];
//         }
//         total  += point0;
//     }
//     //printf("%i\n", total);

//     // Answer2 points
//     int length1 = strlen(answer1);
//     int total1 = 0;
//     int point1 = 0;
//     for (int i = 0; i < length1; i++)
//     {
//         if (answer1[i] >= 97 && answer1[i] <= 122)
//         {
//             point1 = array[answer0[i] - 97];
//         }
//         else
//         {
//             point1 = array[answer0[i] - 65];
//         }
//         total1  += point1;
//     }

//     if (total == total1)
//     {
//         printf("Tie!\n");
//     }
//     else if (total > total1)
//     {
//         printf("Player 1 wins!\n");
//     }
//     else
//     {
//         printf("Player 2 wins!\n");
//     }
// }
