// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
unsigned int word_count , high_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{   
    node *cursor = table[hash(word)];
  
    while(cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0) // checks if words are equal 
        {
            return true;
        }
        cursor = cursor -> next;// if not cursor traverses to the next node in the linked lists of the hash table
    }
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{   
    FILE *file = fopen(dictionary, "r");

    if (file == NULL){
        printf("file unable to opens%s\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];
    while(file != NULL)
    { // reads whole file till the end

        fscanf(file, "*s", word); // reads each character in 
        node *n = malloc(sizeof(node));

         if ( n == NULL)
         {
            return false;
         }

        strcpy(n->word,word);
        hash_value = hash(word);// hashing the value of each word
        n->next = table[hash_value];
        table[hash_value] = n;
        word_count++;
    }
    fclose(file);

    // TODO
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}