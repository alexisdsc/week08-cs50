// This file determines if a number corresponds
// to a credit card and which credit card is
// VISA, AMEX or MASTERCARD. Prints out INVALID if
// the number does not correspond to a valid credita card.

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // declaring initial variables
    long number, number2;
    int digits, first_two_digits, first_digit, sum1, sum2, product, not_valid;
    string number_str;
    bool flag;

    // Ask for a valid number
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);

    // Find length of the number
    flag = true;
    number2 = number;
    sum1 = 0;
    sum2 = 0;
    digits = 0;
    while (flag)
    {
        // Every iteration is one more digit
        digits++;

        // get the numbers and add them
        if (digits % 2 == 0)
        {
            product = 2 * (number2 % 10);
            if (product > 9)
            {
                sum2 += (product / 10) + (product % 10);
            }
            else
            {
                sum2 += product;
            }
        }
        // get the numbers to multiply by 2 and add them
        else
        {
            sum1 += number2 % 10;
        }

        // reduce the number by powers of 10
        number2 = number2 / 10;

        // Store the first 2 digits
        if (number2 < 100 && number2 > 9)
        {
            first_two_digits = number2;
        }
        // Store the first digit
        else if (number2 < 10 && number2 > 0)
        {
            first_digit = number2;
        }
        // End the loop
        else if (number2 == 0)
        {
            flag = false;
        }
    }

    // if sum is a product of 10, then card is valid
    not_valid = (sum1 + sum2) % 10;

    // Check if number belongs to a valid credit card
    if (digits == 15 && (first_two_digits == 34 || first_two_digits == 37) && !not_valid)
    {
        printf("AMEX\n");
    }
    else if (digits == 16 && (first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53 || first_two_digits == 54
                              || first_two_digits == 55) && !not_valid)
    {
        printf("MASTERCARD\n");
    }
    else if ((digits == 13 || digits == 16) && first_digit == 4 && !not_valid)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}