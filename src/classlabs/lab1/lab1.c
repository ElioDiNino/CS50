#include <cs50.h>
#include <stdio.h>

void draw(int height);
bool even(int num);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 10 || height > 20 || even(height) == false);
    draw(height);
}

// Draw a certain height structure
void draw(int height)
{
    // Main repetition
    for (int row = 0; row < height; row++)
    {
        // First and last lines
        if (row == 0 || row == (height - 1))
        {
            for (int lead = 0; lead < 10; lead++)
            {
                printf("#");
            }
            printf("\n");
        }
        // Other lines
        else 
        {
            // Left border
            printf("#");
            
            // Eyes
            if (row == ((height / 2) - 2))
            {
                for (int i = 0; i < 2; i++)
                {
                    printf("  #");
                }
                printf("  ");
                
            }
            
            // Top of mouth
            else if (row == (height / 2))
            {
                printf(" #    # ");
            }
            
            // Main smile
            else if (row == ((height / 2) + 1))
            {
                printf("  ####  ");
            }
            
            // White space
            else
            {
                for (int i = 0; i < 8; i++)
                {
                    printf(" ");
                }
            }
            // Right border
            printf("#\n");
        }
    }
}

/*
// Draw a certain height structure
void draw(int height)
{
    // Main repetition
    for (int row = 0; row < height; row++)
    {
        // First and last lines
        if (row == 0 || row == (height - 1))
        {
            for (int lead = 0; lead < height; lead++)
            {
                printf("#");
            }
            printf("\n");
        }
        // Box with spaces
        else
        {
            printf ("#");
            for (int spaces = 0; spaces < (height - 2); spaces++)
            {
                printf (" ");
            }
            printf ("#\n");
        }
    }
}*/

bool even(int num)
{
    if (num % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}