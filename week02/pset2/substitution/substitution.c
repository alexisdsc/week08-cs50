#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>


// DECLARING HELP FUNCTIONS
string cipher_text(string plaintext, string key);


// MAIN FUNCTION
int main(int argc, string argv[])
{
    // Error handling
    // Check that the user input just one string (argc = 2)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check correct length of the key
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Check for invalid characters (Non letters)
    for (int i = 0; i < 26; i++)
    {
        if (toupper(argv[1][i]) < 65 || toupper(argv[1][i]) > 91)
        {
            printf("Key must contain alphabetic characters.\n");
            return 1;
        }
    }
    // Check for duplicates
    int duplicates_counter;
    for (int i = 0; i < 26; i++)
    {
        // check every letter only exist once
        duplicates_counter = 0;
        char letter = 'A' + i;
        for (int j = 0; j < 26; j++)
        {
            if (letter == argv[1][j])
            {
                // If a lleter in key exist more than once return error
                duplicates_counter++;
                if (duplicates_counter > 1)
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }
        }
    }

    // ask for the plaintext
    string plaintext = get_string("plaintext: ");

    // cipher the text using the key
    string ciphertext = cipher_text(plaintext, argv[1]);

    // Print the ciphered text
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}


// DEFINING HELP FUNCTIONS
string cipher_text(string text, string key)
{
    int len_text = strlen(text);
    int index;

    // Cipher the text
    for (int i = 0; i < len_text; i++)
    {
        // check if the char is an Uppercase Letter
        if (text[i] > 64 && text[i] < 91)
        {
            index = (int) text[i] - 65;
            text[i] = toupper(key[index]);
        }
        // Check if the char is a Lowercase Leter
        else if (text[i] > 96 && text[i] < 123)
        {
            index = (int) text[i] - 97;
            text[i] = tolower(key[index]);
        }
    }

    return text;
}