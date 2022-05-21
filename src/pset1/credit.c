#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Call custom funcitons
string evaluate(long card);
long firstnDigits(long n, long num);
int digits(long n);
bool verify(long card);

// Main function
int main(void)
{
    // Ask for card number
    long card = get_long("Number: ");
    // Evaluate the card
    string output = evaluate(card);
    // Print result
    printf("%s", output);
}

// Check the number of digits, leading numbers, and verify with Luhn’s Algorithm to see if the card is valid
string evaluate(long card)
{
    string result = "INVALID\n";
    if (firstnDigits(1, card) == 4 && (digits(card) == 13 || digits(card) == 16) && verify(card))
    {
        result = "VISA\n";
    }
    else if ((firstnDigits(2, card) == 34 || firstnDigits(2, card) == 37) && digits(card) == 15 && verify(card))
    {
        result = "AMEX\n";
    }
    else if ((firstnDigits(2, card) == 51 || firstnDigits(2, card) == 52 || firstnDigits(2, card) == 53
              || firstnDigits(2, card) == 54 || firstnDigits(2, card) == 55) && digits(card) == 16 && verify(card))
    {
        result = "MASTERCARD\n";
    }
    return result;
}

// Use Luhn’s Algorithm to evaluate the card number
bool verify(long card)
{
    bool boolean = false;
    long calculate = 0;
    long temp;
    long temp2;

    // Go through every other digit starting with the second last
    for (int place = digits(card); place >= 0; place -= 2)
    {
        temp = firstnDigits((place - 1), card);
        // Get the nth digit
        temp = (temp % 10) * 2;
        // If that number is two digits then split them up and add them separately
        if (temp > 9)
        {
            temp2 = firstnDigits(1, temp);
            temp = temp % 10;
            calculate += temp2;
            calculate += temp;
        }
        else
        {
            calculate += temp;
        }
    }
    // Add up all of the other numbers
    for (int place2 = digits(card); place2 >= 0; place2 -= 2)
    {
        temp = firstnDigits((place2), card);
        temp = (temp % 10);
        calculate += temp;
    }
    // See if the final digit is 0 to validate the card number
    if (calculate % 10 == 0)
    {
        boolean = true;
    }
    return boolean;
}

// Determine the number of digits in a number
int digits(long n)
{
    int count = 0;
    while (n != 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

// Evaluate the first n digits of a number
long firstnDigits(long n, long num)
{
    // Remove last digit from number till only n digits are left
    while (num >= pow(10, n))
    {
        num /= 10;
    }
    // Return the first n digits
    return num;
}