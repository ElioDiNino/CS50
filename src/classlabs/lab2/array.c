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
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < array[i]; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}