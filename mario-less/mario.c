#include <cs50.h>
#include <stdio.h>

void pyramid(int y);

int main(void)
{
    int y;

        // user imput for height
    do
    {
        y = get_int("What's the height of the pyramid: ");
    }
    while (y > 8 || y < 1);

// procedure to build the pyramid
    pyramid(y);

}

void pyramid(int y)
{
        // loops for the height entered
    for ( i int i = 0;< y; i++)
    {

        //print necessary "spaces" for row
        for (int j = y - (i + 1); j > 0; j--)
        {
            printf(" ");
        }

        //print necessary # for first pyramid row
        for (int q = y - (i + 1); q < y; q++)
        {
            printf("#");
        }

            //print space between each pyramid
        printf("  ");

        //print necessary # for second pyramid row
        for (int q = y - (i + 1); q < y; q++)
        {
            printf("#");
        }

        //break the line for next row
        printf("\n");
    }
}
