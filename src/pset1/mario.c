#include <cs50.h>
#include <stdio.h>

void draw(int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    draw(height);
}

// Draw a certain height structure
void draw(int height)
{
    // Main repetition
    for (int row = 0; row < height; row++)
    {
        // Leading spaces
        for (int space = 0; space < (height - row - 1); space++)
        {
            printf(" ");
        }
        // Left side hashes
        for (int hash = 0; hash < row + 1; hash++)
        {
            printf("#");
        }
        // Middle space
        printf("  ");
        // Right side hashes
        for (int right = 0; right < row + 1; right++)
        {
            printf("#");
        }
        // New line
        printf("\n");
    }
}