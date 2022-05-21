// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Keep track of the dictionary size
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get the word's hash value
    int hash_value = hash(word);
    
    node *n = table[hash_value];
    
    // Search linked list, looking for word
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Adapted version of the djb2 hash algorithm
    
    // Function should take a string and return an index
    unsigned long hash = 5381;
    int c = tolower(*word);

    while (*word != 0)
    {
        hash = ((hash << 5) + hash) + c;
        c = tolower(*word++);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary
    FILE *loc = fopen(dictionary, "r");
    
    // If there is an error, return false
    if (loc == NULL)
    {
        return false;
    }
    
    // Initialize word array
    char next_word[LENGTH + 1];
    
    // Read strings from file one at a time
    while (fscanf(loc, "%s", next_word) != EOF)
    {
        // Create new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // Copy word into node
        strcpy(n->word, next_word);
        // Hash word to obtain hash value
        int hash_value = hash(next_word);
        // Insert node into hash table at that location
        n->next = table[hash_value];
        table[hash_value] = n;
        dict_size++;
    }
    // Close file
    fclose(loc);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Print out the size variable
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Go through every array entry
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        
        // Cycle through each list entry until the end is reached
        while (n != NULL)
        {
            node *temp = n;
            n = n->next;
            free(temp);
        }
        
        // Return true once everything has been freed
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}

// Help from: https://joseph28robinson.medium.com/cs50-pset-5-speller-f9c89d08237e