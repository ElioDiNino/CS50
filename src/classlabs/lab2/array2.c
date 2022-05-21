#include <cs50.h>
#include <stdio.h>

void draw(int size, int array[]);

int main(void)
{
    int size = get_int("What is the array size? ");
    int input[size];
    for (int i = 0; i < size; i++)
    {
        input[i] = get_int("Value %i: ", i + 1);
    }
    draw(size, input);
}

void draw(int size, int array[])
{
    int highest = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] > highest)
        {
            highest = array[i];
        }
    }
    for (int n = 0; n < highest; n++)
    {
        int space = 0;
        for (int i = 0; i < size; i++)
        {
            if (array[i] >= highest - n)
            {
                for (int j = 0; j < i - space; j++)
                {
                    printf(" ");
                }
                printf("#");
                space = i + 1;
            }
        }
        printf("\n");
    }
}