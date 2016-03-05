/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

typedef struct node
{
    bool word_last;
    struct node* children[27];
    
}
node;

int count = 0;
node* root;

//Returns true if the char is valid
 
bool valid(char letter)
{
	if (letter < 'A')
		return (letter == '\n' || letter == '\'');
	if (letter > 'Z')
		return (letter >= 'a' && letter <= 'z');
	else
	return false;
}

//"tolower" version for pointer argument

char toLower(char letter)
{
	if (letter >= 'A' && letter <= 'Z')
		letter += ('a' - 'A');

	return letter;
}

//Converts a char into index 

int indexval(char letter)
{
	if (letter == '\'')
		return 26;
	else
		return letter - 'a';
}

// Function that letter to corresponding alphabetical number
unsigned int convert(char c)
{
    if(c == '\'')
    	c = 26;

    else if (c != '\0' || c != '\n')
    	c = (toupper(c)) - 'A';

    return c;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char* ptr = malloc(sizeof(char) * strlen(word));
	strcpy(ptr, word);
	node* current = root;
	while(*ptr != '\0')
	{
		*ptr = toLower(*ptr);
		int index = indexval(*ptr);
		if (current->children[index] == NULL)
			return false;
		else
			current = current->children[index];
		ptr++;
	}
    return current->word_last;
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
   FILE* file = fopen(dictionary, "r");
	
	if(file == NULL)
	{
		printf("Dictionary Not Found!\n");
		return false;
	}

	char* buffer = malloc(sizeof(char));

	node* current = root = malloc(sizeof(node));
	
	// character by character iteration
	while(fread(buffer, sizeof(char), 1, file))
	{
		if(valid(*buffer))
		{
			*buffer = toLower(*buffer);

			if(*buffer == '\n')
			{
				if(current != root && 
					!current->word_last &&
					current != NULL)
				{

					current->word_last = true;
					count++;
					current = root;
				}
			}

			else
			{	

				int index = indexval(*buffer);
				if(current->children[index] == NULL)
				{	
					node* new_node = malloc(sizeof(node));

					if(new_node == NULL)
						return false;

					for(int i=0; i<27; i++)
						new_node->children[i] = NULL;

					current->children[index] = new_node;
				}	
				current = current->children[index];
			}
		}
	}
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{

    return count;
}

void unloadHelper(node* current)
{
	for(int i=0; i<27; i++)
	{
		if(current->children[i] != NULL)
			unloadHelper(current->children[i]);
	}
	free(current);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    unloadHelper(root);
    return true;
}
