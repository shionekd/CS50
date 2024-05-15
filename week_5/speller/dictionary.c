// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

unsigned int counts = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to obtain its hash value
    int value = hash(word);

    // Search the hash table at the location specified by the word’s hash value
    node *cursor = table[value];
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
    unsigned int index = 0;
    index = toupper(word[0]) - 'A';
    // printf("word[0] : %i\n", word[0]);
    // printf("index num : %i\n", index);
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];

    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return 1;
    }
    // Read each word in the file
    while (fscanf(source, "%s", word) != EOF)
    {
        // Copy the word into the new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("We have an error to make a new node\n");
            fclose(source);
            return 1;
        }

        strcpy(new_node->word, word);
        new_node->next = NULL;

        int index = hash(word);

        if (table[index] == NULL)
        {
            table[index] = new_node;
        }
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }
        counts++;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counts;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp = NULL;
    node *cursor = NULL;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
