#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");
    int digit = 0;
    long digitNum = number;

    // check digit number
    while (digitNum / 10 > 0)
    {
        digitNum = digitNum / 10;
        digit++;
    }
    digit += 1;

    // sum 1
    long firstSumNum = number / 10;
    long firstSum = 0;
    long totalSum = 0;
    long SumDig = digit / 2;
    for (int i = 1; i <= SumDig; i++)
    {
        firstSum = firstSumNum % 10 * 2;
        firstSumNum = firstSumNum / 100;
        totalSum += firstSum / 10 + firstSum % 10;
    }

    // sum2
    long secondSum = 0;
    long secondSumNum = number;
    if (digit % 2 != 0)
    {
        SumDig++;
    }
    for (int i = 1; i <= SumDig; i++)
    {
        secondSum = secondSumNum % 10;
        secondSumNum = secondSumNum / 100;
        totalSum += secondSum;
    }

    // alt approach1 loop
    // int currentNumber = number;
    // int sum1 = 0;
    // int sum2 = 0;
    // for (int i = 0; i < digit; i++)
    // {
    //     int currentDigit = currentNumber % 10;
    //     if(i % 2 == 0)
    //     {
    //         // even digit
    //         sum1 += currentDigit;
    //     }
    //     else
    //     {
    //         // odd digit
    //         int multi = currentDigit * 2;
    //         sum2 += multi / 10;
    //         sum2 += multi % 10;
    //     }
    // }
    // int finalSum = sum1 + sum2;

    // cheking card type
    if (totalSum % 10 == 0)
    {
        long creditNum15_2 = number / 10000000000000;
        long creditNum16_2 = number / 100000000000000;
        if (digit == 15)
        {
            if (creditNum15_2 == 34 || creditNum15_2 == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digit == 16)
        {
            if (number / 1000000000000000 == 4)
            {
                printf("VISA\n");
            }
            else if (creditNum16_2 == 51 || creditNum16_2 == 52 || creditNum16_2 == 53 || creditNum16_2 == 54 ||
                     creditNum16_2 == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digit == 13)
        {
            if (number / 1000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
