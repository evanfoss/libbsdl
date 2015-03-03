/*
 * libbsdl.c
 * by Evan Foss
 * 2015.01.20
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Copyright 2015.02.02 Evan Foss
 *
 */

//I don't think I need these but it can't hurt to make the preprocessor earn it's keep
#ifndef LIBBSDL_C_
#define LIBBSDL_C_

#include <stdio.h>
/* When I first did this I was getting warnings from the compiler about 
 * incompatible implicite delarations. The strlen function in stdlib.h 
 * causes this. Please stick to the one in string.h
 */
#include <stdlib.h>
#include <string.h>
#include "libbsdl.h"


#define WORD_COUNT 16
#define WORD_LENGTH_MAX 10

struct bsdl_node
{
	struct bsdl_node *next;
	char *name;
	char *value;
	struct bsdl_node *sub;
};


/* 
 *
 */
extern void libbsdl_preprocessor(FILE *file)
{

	unsigned int location = 0;
	size_t len = 0;
	// if the file we have been given is not there lets stop now.
	if (file == NULL)
	{
		return;
	}
	// create head node
	
	// call recursive function
	libbsdl_preprocessor_populate(file, &len);
	// is nead node address still a null pointer
	// if yes then the file is empty it does not
	// matter yes or know because we still return
	// the same way.
	
	return;
}

/*
 * 
 */
void libbsdl_preprocessor_populate(FILE *file, size_t *len)
{
	unsigned int count = 0;
	// the line we are on
	char *line = NULL;
	// length of the line we are on
	ssize_t read;
	// the location in the line we are looking at
	unsigned int location = 0;
	// how many ( marks have we seen?
	unsigned int parenthesis = 0;
	// look at the file line by line
	while ((read = getline(&line, len, file)) != -1)
	{
		location = 0;
		libbsdl_line_preprocessor(read, line, location);
		count++;
	}
	if ( 0 > parenthesis )
	{
		// immediate none recoverable syntax error
	}
	printf("\n");
	printf("lines %d", count);
	printf("\n\n");
	free(line);
	return;
}
/*
void libbsdl_preprocessor_getdata(char *line, struct bsdl_node *node)
{
	return;
}
*/

/* 
 * This function really does not read a whole line. What it does is recrusvily process a line one segment at a time. 
 * 
 *
 *
 */
int libbsdl_line_preprocessor(ssize_t line_length, char line[], int location)
{
	// word flag has two positions S = set (just found a word) and R = reset (no word on this line) note that this excludes comments
	char word_flag = 'R';
	// the number of words we have found so far
	unsigned int count = 0;
	// how many " marks have we seen?
	unsigned int quote = 0;
	// the number corsponding to the word we are looking for right now
	unsigned int word_number = 0;
	// the length of the word we are looking for
	unsigned short word_length = 0;
	// the words we have to look for *NEVER CHANGE THE ORDER* only add onto the end of this list if you must
	char words[WORD_COUNT][WORD_LENGTH_MAX] = {"--\0", "string", "of", "is", "signal", "vector", "entity\0", "generic\0", "constant\0", "use\0", "attribute\0", "port\0", "type\0", "subtype\0", "package\0", "end\0"};

	// make sure we have not hit the end of the line (terminal case for recursion)
	if ( line_length <= location )
	{
		return 0;
	}

	for (location = 0; location < line_length - 1; location++)
	{
		word_flag = 'R';
		for (word_number = 0; word_number < WORD_COUNT; word_number++)	
		{
			if ( 1 == libbsdl_offset_is_word(line, words[word_number], location))
			{
				count++;
				printf(" count %d", count);
				printf(" location %d", location);
				printf(" word %s", words[word_number]);
				printf(" line %s", line);
				// if we are in the first word which is -- then we are in a comment so skip the rest of the line
				if ( 0 == word_number )
				{
					location = line_length;
					word_flag = 'R';
					// copy the rest of the line to a comment node
					return 0;
				}
				else
				{
					location += strlen(words[word_number]);
					word_flag = 'S';
					return 0;
					// call this function again
				}
				word_number = WORD_COUNT + 1;
			}
		}
	}
	// the following should eventually become a switch case statement
	if ( 0 != quote )
	{
		// immediate none recoverable syntax error
		return -1;
	}
	return 0;
}


/* 
 * This function tests for a word in a line of text in a specific location with case insenitivity.
 * It does this slightly faster than a normal strncasecmp. 
 *
 */
int libbsdl_offset_is_word(char line[], char word[], unsigned int offset)
{
	unsigned int word_length = 0;
	word_length = strlen(word);
	if ( offset > (word_length - 1) && 1 != libbsdl_is_whitespace(line, (offset - 1) ) )
	{
		return 0;
	}
	else if ( ' ' == line[word_length + offset] )
	{
		if ( 0 == strncasecmp( &line[offset],word, word_length ) )
		{
			return 1;
		}
	}
	return 0;
}

/*
 * The following is just to test if a character in a string is whitespace.
 * Whitespace is defined as a space, tab, or newline.
 */
int libbsdl_is_whitespace(char line[], unsigned int number)
{
	char ascii_space = ' ';
	char ascii_tab = '\t';
	char ascii_newline = '\n';
	char ascii_terminate = '\0';
	// if we have recieved a negative array location or one off the end of the array something evil has happened
	if ( number < 0 || number > ( strlen(line) - 1 ) )
	{
		return 0;
	}
	if ( line[number] == ascii_space || line[number] == ascii_tab || line[number] == ascii_newline || line[number] == ascii_terminate )
	{
		return 1;
	}
	return 0;
}

extern void libbsdl_initial_comments(FILE *file)
{

	unsigned int location = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, file)) != -1)
	{
		// loop from 0 to the end of line minus the length of the string.
		for (location = 0; location < read - 1; location++)
		{
			// if true then we found the comment
			if (line[location] == '-' && line[location + 1] == '-')
			{
				printf("%s", line);
			}
			else if (line[location] =! ' ')
			{
				location == read;
			}
		}
//		printf("Retrieved line of length %zu :\n", read);
//		printf("counted to %zu", location);
//		printf("\n");
	}
	free(line);	
	return;
}

/*
 * Because of the way we are just stepping down the lines of the file 
 * there is no need to impliment adding nodes in the middle of the list 
 * only on the end. That is what this function does.
 */
struct bsdl_node *libbsdl_ll_new_node(struct bsdl_node *last_node)
{
	struct bsdl_node *next_node;
	next_node = malloc(sizeof(struct bsdl_node));
	if (next_node == NULL)
	{
		exit(EXIT_FAILURE);
	}
	next_node->next = NULL;
	if (last_node->next != NULL)
	{
		last_node->next = next_node;
	}
	return next_node;
}
/*
struct bsdl_node *libbsdl_ll_new_subnode(struct bsdl_node *subhead)
{
	return;
}

struct bsdl_node *libbsdl_ll_previous_node(struct bsdl_node *node)
{
}

struct bsdl_node *libbsdl_ll_previous_subnode(struct bsdl_node *node)
{
}

void libbsdl_ll_del_subnode(struct bsdl_node *subnode)
{
	return;
}

void libbsdl_ll_del_list(struct bsdl_node *head)
{
	return;
}

void libbsdl_ll_del_sublist(struct bsdl_node *subhead)
{
	return;
}
*/

#endif

