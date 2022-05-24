#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Define basic types and units
// unsigned integer of 1 byte (8 bits)
typedef uint8_t BYTE;
#define BLOCKSIZE 512

int main(int argc, char *argv[])
{
    // Check for correct number of inputs
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover IMAGE_SOURCE\n");
        return 1;
    }

    // open the CARD File
    FILE *rawfile = fopen(argv[1], "r");
    // Check correctness
    if (rawfile == NULL)
    {
        fprintf(stderr, "Source not found.\n");
        return 2;
    }

    // Output file
    FILE *imgfile = NULL;
    // buffer
    BYTE buffer[BLOCKSIZE];

    // image counter
    int img_counter = 0;

    while (fread(buffer, sizeof(BYTE), BLOCKSIZE, rawfile) == BLOCKSIZE)
    {
        // Check if new JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close old file
            if (imgfile != NULL)
            {
                fclose(imgfile);
            }

            // Set the name for the new image
            char filename[8];
            sprintf(filename, "%03d.jpg", img_counter);

            imgfile = fopen(filename, "w");

            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, imgfile);

            img_counter++;
        }
        else if (imgfile != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, imgfile);
        }
    }

    // Close files
    fclose(rawfile);
    if (imgfile != NULL)
    {
        fclose(imgfile);
    }

}