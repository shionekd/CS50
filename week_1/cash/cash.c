#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    int counts = 0;
    // quarters
    if (cents >= 25)
    {
        counts = cents / 25;
        cents = cents % 25;
    }
    // dimes
    if (cents >= 10)
    {
        counts = counts + cents / 10;
        cents = cents % 10;
    }
    // nickels
    if (cents >= 5)
    {
        counts = counts + cents / 5;
        cents = cents % 5;
    }
    // yespennies
    if (cents < 5)
    {
        counts = counts + cents;
    }

    printf("%d\n", counts);
}
