"""
Usage:
$ python credit.py

About the program:
Thi program detects if a certain chain of digits is a VALID credit card or not.
if it is VALID, this program prompts AMEX, MASTERCARD, or VISA.
otherwise prompts INVALID.

Example:
$ python credit.py
Number: 378282246310005
AMEX

$ python credit.py
Number: 1234
INVALID
"""


# MAIN
def main():
    nstring = -1
    # get valid digits
    while True:
        n = input("Number: ")
        if n.isdigit():
            break

    # split the number into an individual digits list
    digits = list(n)

    # validity checker variables
    checksum_valid = False
    number_digits = len(n)
    first_digit = n[:1]
    first_2_digits = n[:2]
    # valid starter digits
    amex_valid = ["34", "37"]
    mastercard_valid = ["51", "52", "53", "54", "55"]
    visa_valid = ["4"]

    # Step 1 and 2
    counter, addition1, addition2 = 1, 0, 0
    for digit in reversed(digits):
        # Step 1: Multiply every other digit by 2 and add their individual digits
        if counter % 2 == 0:
            product = 2*int(digit)
            addition2 += sum_digits(product)
        # Step 2: Add to the sum digts weren't multiplied by 2
        else:
            addition1 += int(digit)
        counter += 1

    # Step 3: If total sum is divisible by 10, then is valid
    if (addition1 + addition2) % 10 == 0:
        checksum_valid = True

    # Prompt validity and brand
    if checksum_valid and first_2_digits in amex_valid and number_digits == 15:
        print("AMEX")
    elif checksum_valid and first_2_digits in mastercard_valid and number_digits == 16:
        print("MASTERCARD")
    elif checksum_valid and first_digit in visa_valid and (number_digits == 13 or number_digits == 16):
        print("VISA")
    else:
        print("INVALID")


# AUXILIAR FUNCTIONS
def sum_digits(n):
    """int->int

    Description:
    This function adds every digit of n individually and returns
    the total sum.
    """
    sum = 0
    # If there are more than 1 digit add them individually
    if n > 9:
        while n > 0:
            sum += n % 10
            n = int(n/10)
        return sum
    # if only a single digit return the same digit
    else:
        return n


if __name__ == "__main__":
    main()