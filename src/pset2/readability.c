#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Custom functions
int num_letters(string text);
int num_words(string text);
int num_sentences(string text);
int grade_level(int letters, int words, int sentences);

// Main function
int main(void)
{
    // Asks the user for a block of text to evaluate
    string text = get_string("Text: ");

    // Evaluates the number of letters
    int total_letters = num_letters(text);
    //printf("%i letter(s)\n", total_letters);

    // Evaluates the number of words
    int total_words = num_words(text);
    //printf("%i word(s)\n", total_words);

    // Evaluates the number of sentences
    int total_sentences = num_sentences(text);
    //printf("%i sentence(s)\n", total_sentences);

    // Evaluates the grade level
    int grade = grade_level(total_letters, total_words, total_sentences);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Evaluates the number of letters
int num_letters(string text)
{
    int string_length = strlen(text);
    int total = 0;

    for (int i = 0; i < string_length; i++)
    {
        if (isalpha(text[i]))
        {
            total += 1;
        }
    }
    return total;
}

// Evaluates the number of words
int num_words(string text)
{
    int string_length = strlen(text);
    int total = 1;

    for (int i = 0; i < string_length; i++)
    {
        if (text[i] == ' ')
        {
            total += 1;
        }
    }
    return total;
}

// Evaluates the number of sentences
int num_sentences(string text)
{
    int string_length = strlen(text);
    int total = 0;

    for (int i = 0; i < string_length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            total += 1;
        }
    }
    return total;
}

// Evaluates and returns the grade level
int grade_level(int letters, int words, int sentences)
{
    float L = ((float) letters / (float) words) * 100;
    float S = ((float) sentences / (float) words) * 100;
    float grade = 0.0588 * L - 0.296 * S - 15.8;
    int final_grade = round(grade);
    return final_grade;
}