#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

// Functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float coleman_liau(int letters, int words, int sentences);

int main(void)
{
    // Get the text
    string text = get_string("Text: ");

    // Count the letters
    int num_letters = count_letters(text);

    // Count the words
    int num_words = count_words(text);

    // Count the sentences
    int num_sentences = count_sentences(text);

    float index = coleman_liau(num_letters, num_words, num_sentences);

    // Grade level
    int grade = (int) round(index);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }


}

// HELPER FUNCTIONS

// Letter count
int count_letters(string text)
{
    // local variables
    int letter_counter = 0;
    int len_text = strlen(text);

    // count the letters
    for (int i = 0; i < len_text; i++)
    {
        // Only letters!
        if (toupper(text[i]) > 64 && toupper(text[i]) < 91)
        {
            letter_counter++;
        }
    }

    return letter_counter;
}

// Words count
int count_words(string text)
{
    // local variables
    int word_counter = 0;
    int len_text = strlen(text);

    // count the words
    for (int i = 0; i < len_text; i++)
    {
        // Words are separated by spaces!
        if (text[i] == 32)
        {
            word_counter++;
        }
    }

    return word_counter + 1;
}

// Sentences count
int count_sentences(string text)
{
    // local variables
    int sentence_counter = 0;
    int len_text = strlen(text);

    //count the senteces.
    for (int i = 0; i < len_text; i++)
    {
        // Sentences are separated by '.', '!' or, '?'
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentence_counter++;
        }
    }

    return sentence_counter;
}

// Get the grade of the text
float coleman_liau(int letters, int words, int sentences)
{
    // local variables
    float L, S, index;

    // compute L
    L = (100.0 / words) * letters;

    // compute S
    S = (100.0 / words) * sentences;

    // compute the index
    index = 0.0588 * L - 0.296 * S - 15.8;

    return index;
}