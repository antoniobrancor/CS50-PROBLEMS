#include <cs50.h>
#include <stdio.h>

int main(void)

{
    long CardNumber;

    // get credit card number
    CardNumber = get_long("Credit card number: ");

    int sumOrMult = 0;
    int multiplySum = 0;
    int naoTaUsando = 0;
    int digitCount = 0;
    int firstTwoDigits = 0;

    // runs for each digit validation and necessary actions
    for (int i = 10; CardNumber >= 1; CardNumber = CardNumber / 10)
    {
        digitCount++;
        if (CardNumber < 100 && firstTwoDigits == 0)
        {
            firstTwoDigits = ((CardNumber % 100));
        }
        if (sumOrMult == 0)
        {
            multiplySum = multiplySum + (CardNumber % 10);
            sumOrMult = 1;
        }
        else
        {
            if ((CardNumber % 10) * 2 >= 10)
            {
                multiplySum = multiplySum + ((CardNumber % 10) * 2 - 9);
            }
            else
            {
                multiplySum = multiplySum + (CardNumber % 10) * 2;
            }
            sumOrMult = 0;
        }
    }

    // print results based on values
    if (multiplySum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if (digitCount >= 13 && digitCount <= 16 && (firstTwoDigits / 10 == 4))
        {
            printf("VISA\n");
        }
        else if (digitCount == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
        {
            printf("AMEX\n");
        }
        else if (digitCount == 16 && (firstTwoDigits >= 51 && firstTwoDigits <= 55))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
