#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for starting population size
    int start;
    do
    {
        start = get_int("Start size: ");
        if (start < 9)
        {
            printf("Please provide a larger population size\n");
        }
    }
    while (start < 9);
    // Prompt for final population size
    int end;
    do
    {
        end = get_int("End size: ");
        if (end < start)
        {
            printf("Please provide a size bigger than the start size\n");
        }
    }
    while (end < start);
    // Calculate number of years until we reach threshold
    int years = 0;
    int result = start;
    while (result < end)
    {
        int add = result / 3;
        int sub = result / 4;
        result = result + add - sub;
        years++;
    }
    // Print number of years
    printf("Years: %i\n", years);
}