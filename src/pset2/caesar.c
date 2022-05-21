#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Custom functions
string encode_text(int key, string text);
bool num_check(string key);

// Main function
int main(int argc, string key[])
{
    // Check command-line input
    if (argc != 2 || num_check(key[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Run regular code if other tests are passed
    else
    {
        string plain_text = get_string("plaintext: ");
        int num_key = atoi(key[1]);
        string encoded_text = encode_text(num_key, plain_text);
        printf("ciphertext: %s\n", encoded_text);
        return 0;
    }
}

string encode_text(int key, string text)
{
    string encrypted = text;
    int length = strlen(text);
    int reduce_key = key % 26;
    
    // Take inputted text and shift by key places
    for (int i = 0; i < length; i++)
    {
        // Checks if the text is an alphabetic character
        if (isalpha(text[i]))
        {
            // Checks if the text is upper or lowercase
            if (isupper(text[i]))
            {
                encrypted[i] = (encrypted[i] - 64 + reduce_key) % 26;
                encrypted[i] += 64;
            }
            else if (islower(text[i]))
            {
                encrypted[i] = (encrypted[i] - 96 + reduce_key) % 26;
                encrypted[i] += 96;
            }
        }
    }
    return encrypted;
}

// Check if the inputed string is a valid integers
bool num_check(string key)
{
    int length = strlen(key);
    bool result = true;
    
    for (int i = 0; i < length; i++)
    {
        if (isdigit(key[i]) == false)
        {
            result = false;
        }
    }
    return result;
}