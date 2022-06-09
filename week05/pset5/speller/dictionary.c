// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// include strcpy
#include <string.h>
// includes strcasecmp
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODOs:
// Choose number of buckets in hash table
//const unsigned int N = 26;
const unsigned int N = 1170;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODOs:
    // Hash the word
    int index = hash(word);
    // node checker
    node *cursor = table[index];

    // Check if words match. Otherwise go to the next node.
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /* Improve this hash function */
    int len = strlen(word);
    return len * (toupper(word[0]) - 'A');

    //return toupper(word[0]) - 'A';
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Init global variable
    dictionary_size = 0;
    // Open Directory file
    FILE *dictfile = fopen(dictionary, "r");
    if (dictfile == NULL)
    {
        return false;
    }

    // read strings from the file one at a time
    char curword[LENGTH + 1];
    int hashindex = 0;
    while (fscanf(dictfile, "%s", curword) != EOF)
    {
        // Create a new node for each word
        node *nw = malloc(sizeof(node));
        nw->next = NULL;
        if (nw == NULL)
        {
            printf("Word allocation failed!\n");
            return false;
        }
        // Insert new word into the node
        strcpy(nw->word, curword);
        // Hash word to obtain a hash table
        hashindex = hash(nw->word);

        // Link the node to the hash table
        if (table[hashindex] == NULL)
        {
            table[hashindex] = nw;
        }
        else
        {
            nw->next = table[hashindex];
            table[hashindex] = nw;
        }
        dictionary_size++;
    }

    // Free pointer file
    fclose(dictfile);

    // True: Successful. False: Failed
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Free all memory pointers of every index
    for (int i = 0; i < N; i++)
    {
        // Set the pointers to the first element of the current index
        node *tmp = table[i];
        node *cursor = table[i];

        // Free all the nodes linked to the current index
        while (cursor != NULL)
        {
            // Go to the next node if it is not NULL
            if (cursor->next != NULL)
            {
                cursor = cursor->next;
                // free current node
                free(tmp);
                // assign tmp to the next node
                tmp = cursor;
            }
            else
            {
                free(cursor);
                break;
            }
        }
    }

    return true;
}
