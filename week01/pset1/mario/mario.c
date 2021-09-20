// This program prints the Mario's Pyramids
// from the heights of 1 to 8.

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    // Ask for the height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Define the width based on height
    //int width = 2*height + 2;

    // Print the Pyramids
    for (int level = height; level > 0; level--)
    {
        // left spaces
        for (int left_spaces = level - 1; left_spaces > 0; left_spaces--)
        {
            printf(" ");
        }
        // left hashes
        for (int left_hashes = height - (level - 1); left_hashes > 0; left_hashes--)
        {
            printf("#");
        }

        // Gap
        printf("  ");

        // right hashes
        for (int right_hashes = height - (level - 1); right_hashes > 0; right_hashes--)
        {
            printf("#");
        }
        // Right spaces
        //for (int right_spaces = level - 1; right_spaces > 0; right_spaces--)
        //{
        //    printf(" ");
        //}
        // Next level
        printf("\n");
    }
}