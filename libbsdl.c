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


#define WORD_COUNT 15
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
	unsigned int depth = 0;
	char mode = 'w';
	// look at the file line by line
	while ((read = getline(&line, len, file)) != -1)
	{
		location = 0;
		printf("\n");
		printf("%s", line);
		printf("\n");
		libbsdl_line_preprocessor(read, line, count, location, mode, depth);
		count++;
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
int libbsdl_line_preprocessor(ssize_t line_length, char line[], unsigned int line_number, unsigned int location, char mode, unsigned int depth)
{
	// the number corsponding to the word we are looking for right now
	unsigned int word_number = 0;
	// the words we have to look for *NEVER CHANGE THE ORDER* only add onto the end of this list if you must
	char words[WORD_COUNT][WORD_LENGTH_MAX] = {"string\0", "of\0", "is\0", "signal\0", "vector\0", "entity\0", "generic\0", "constant\0", "use\0", "attribute\0", "port\0", "type\0", "subtype\0", "package\0", "end\0"};
	char comment[2] = {"--"};
	unsigned int marker = 0;
	// fail if we exit after an arbitrarily excessive depth
	if ( depth > 50 )
	{
		return -1;
	}
	location = libbsdl_end_of_whitespace(line, location);
	// make sure we have not hit the end of the line (terminal case for recursion)
	if ( line_length <= location )
	{
		return 0;
	}
	printf("depth %d", depth);
	printf("\n");
	depth++;
	if ( '-' == line[location] && '-' == line[location + 1] )
	{
		//this line is most likely a comment
		//if ( location + 1 <= line_length )
		printf(" location %d", location);
		printf(" comment detected\n");
		printf("\n");
		return 0;
	} else
	if ( ':' == line[location] )
	{
		printf(" location %d", location);
		if ( '=' == line[location + 1] )
		{
			printf(" := (equivilence) \n");
		} else
		{
			printf(" : (assignment of) \n");
		}
	} else
	if ( '"' == line[location] )
	{
		mode = '"';
		// look ahead for second quote mark and copy bulk then go to that location + 1
		printf(" location %d", location);
		printf(" string open\n");
		location++;
		location = libbsdl_line_search_char(line, location, '"');
		printf(" location %d", location);
		printf(" string closed\n");
	} else
	if ( '"' == mode )
	{
		if ( ';' == line[location] )
		{       
			printf(" location %d", location);
			printf(" string end\n");
			mode = 'w';
		}       
		if ( '&' == line[location] )
		{       
			printf(" location %d", location);
			printf(" more string left\n");
		}
	} else
	if ( 'd' != mode )
	{
		if ( ';' == line[location] )
		{       
			printf(" location %d", location);
			printf(" end of words\n");
		} else
		for (word_number = 0; word_number < WORD_COUNT; word_number++)	
		{	
			if ( 1 == libbsdl_offset_is_word(line, words[word_number], location))
			{
				printf(" location %d", location);
				printf(" word %s", words[word_number]);
				printf("\n");
				//location += strlen(words[word_number]);
				word_number = WORD_COUNT + 1;
			}
		}
	}
	location++;
	return libbsdl_line_preprocessor(line_length, line, line_number, location, mode, depth);
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
 * Skip white space. It pretty much is what it says.
 *
 */
int libbsdl_end_of_whitespace(char line[], unsigned int number)
{
	unsigned int current_location;
	unsigned int length;
	length = strlen(line);
	while ( ( number < length ) && ( 0 > libbsdl_is_whitespace(line, number) ) )
	{
		number++;
	}
	return number;
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

/* 
 * Search for a character ahead of a given location.
 * -1 means the character was not found. One means it did.
 */
int libbsdl_line_search_char(char line[], unsigned int offset, char looking_for)
{
	unsigned int location;
	unsigned int line_length = 0;
	line_length = strlen(line) - 1;
	for (location = offset; location < line_length;location++)
	{
		if ( looking_for == line[location] )
		{
			return location;
		}
	}
	return -1;
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
			if ('-' == line[location] && '-' == line[location + 1])
			{
				printf("%s", line);
			}
			else if (' ' != line[location] )
			{
				location = read;
			}
		}
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

