#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define a byte and the number of pictures
typedef uint8_t BYTE;
int count = 0;

int main(int argc, char *argv[])
{
    // Make sure only one argument is passed
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Make sure the file can be opened
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open \"%s\".\n", argv[1]);
        return 1;
    }

    // Create the buffer, filename, and output file
    BYTE buffer[512];
    char *filename = malloc(8);
    FILE *output = NULL;

    // Cycle through the data at the buffer size and look for the jpg header
    while (fread(buffer, sizeof(buffer), 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Check if it's the first file, create the file
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("Could not create file.\n");
                }
            }
            // If it's not, close the previous file then create a new one
            else
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", count);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("Could not create file.\n");
                }
            }
            // Write the first block to the jpg
            fwrite(buffer, sizeof(buffer), 1, output);
            count += 1;
        }
        // Copy data into the file until another jpg header is found
        else
        {
            if (output != NULL)
            {
                fwrite(buffer, sizeof(buffer), 1, output);
            }
        }
    }
    free(filename);
    fclose(file);
    fclose(output);
    return 0;
}