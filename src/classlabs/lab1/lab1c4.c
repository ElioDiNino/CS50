#include <cs50.h>
#include <stdio.h>

// Custom functiona
void draw(int height);
bool div3(int num);

// Main function
int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    // Makes sure the number is in between 9 and 21 while also checking if it is divisable by 3
    while (height < 9 || height > 21 || div3(height) == false);
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
            for (int lead = 0; lead < height; lead++)
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
            if (row == ((height / 3) - 1))
            {
                for (int col = 1; col < height - 1; col++)
                {
                    if (col == (height / 3) || col == (((height / 3) * 2) - 1))
                    {
                        printf("#");
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }

            // Top of mouth
            else if (row == ((height / 3) * 2) - 1)
            {
                for (int col = 1; col < height - 1; col++)
                {
                    if (col == ((height / 3) - 1) || col == (height - (height / 3)))
                    {
                        printf("#");
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }

            // Main smile
            else if (row == ((height / 3) * 2))
            {
                for (int col = 1; col < height - 1; col++)
                {
                    if (col > ((height / 3) - 1) && col < (height - height / 3))
                    {
                        printf("#");
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }

            // White space
            else
            {
                for (int i = 0; i < height - 2; i++)
                {
                    printf(" ");
                }
            }
            // Right border
            printf("#\n");
        }
    }
}

// Checks if the number is divisable by 3
bool div3(int num)
{
    if (num % 3 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}