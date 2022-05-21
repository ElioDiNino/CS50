#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Custom functions
string encode_text(string key, string text);
bool word_check(string key);
bool repeat_check(string key);
string make_upper(string text);

// Main function
int main(int argc, string key[])
{
    // Check command-line input
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check if there are 26 characters
    else if (strlen(key[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Check if there is a non-alphabetical character
    else if (word_check(key[1]) == false)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    // Check if a letter is repeated
    else if (repeat_check(make_upper(key[1])))
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    // Run regular code if other tests are passed
    else
    {
        string plain_text = get_string("plaintext: ");
        string format_key = make_upper(key[1]);
        string encoded_text = encode_text(format_key, plain_text);
        printf("ciphertext: %s\n", encoded_text);
        return 0;
    }
}

// Encode the provided text
string encode_text(string key, string text)
{
    string encrypted = text;
    int length = strlen(text);

    // Loop through inputted text
    for (int i = 0; i < length; i++)
    {
        // Checks if the text is an alphabetic character
        if (isalpha(text[i]))
        {
            // Checks if the text is upper or lowercase
            if (isupper(text[i]))
            {
                encrypted[i] = key[encrypted[i] - 65];
            }
            else if (islower(text[i]))
            {
                encrypted[i] = tolower(key[encrypted[i] - 97]);
            }
        }
    }
    return encrypted;
}

// Check if the inputed string is a valid integers
bool word_check(string key)
{
    int length = strlen(key);
    bool result = true;

    for (int i = 0; i < length; i++)
    {
        if (isalpha(key[i]) == false)
        {
            result = false;
        }
    }
    return result;
}

// Convert every given key letter to uppercase for consistency
string make_upper(string text)
{
    string upper = text;
    for (int i = 0; i < 26; i++)
    {
        upper[i] = toupper(text[i]);
    }
    return upper;
}

// Check if a character is repeated in the key
bool repeat_check(string key)
{
    for (int kchar = 0; kchar < 26; kchar++)
    {
        for (int cchar = kchar + 1; cchar < 26; cchar++)
        {
            if (key[cchar] == key[kchar])
            {
                return true;
            }
        }
    }
    return false;
}