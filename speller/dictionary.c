// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <strings.h>

#include "dictionary.h"

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

int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int tableIndex = hash(word);
    node *cursor = table[tableIndex];
    while (cursor != NULL)
    {
        printf("\n word %s ", word);
        printf(" cursor word %s ", cursor->word);
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
        printf("new cursor word %s \n", cursor->word);
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, word);
        new_node->next = NULL;
        int index = hash(word);
        if (table[index] != NULL)
        {
            table[index] = new_node;
        }
        else
        {
            node *head = table[index];
            new_node->next = head;
            table[index] = new_node;
        }
        word_count++;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *aux = cursor;
        while (aux != NULL)
        {
            cursor = cursor->next;
            free(aux);
            aux = cursor;
        }
    }
    return true;
}
