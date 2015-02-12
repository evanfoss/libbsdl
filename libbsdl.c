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

#define WORD_COUNT 11
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
	char *line = NULL;
	ssize_t read;
	unsigned int location = 0;
	unsigned int word_number = 0;
	unsigned short word_length = 0;
	char space = ' ';
	char tab = '\t';
	char newline = '\n';
	char words[WORD_COUNT][WORD_LENGTH_MAX] = {"--\0", "entity\0", "generic\0", "constant\0", "use\0", "attribute\0", "port\0", "type\0", "subtype\0", "package\0", "end\0"};
	while ((read = getline(&line, len, file)) != -1)
	{
		for (location = 0; location < read - 1; location++)
		{
			for (word_number = 0; word_number < WORD_COUNT; word_number++)
			{
				word_length = strlen(words[word_number]);
				// now i just need to clean up this bit.. and write a function to process the data that follows these tokens
				if ( ( 0 == strncasecmp( &line[location],words[word_number], word_length ) ) && ( 0 == strncmp( &line[location + word_length + 1], &space, 1) || 0 == strncmp( &line[location + word_length + 1], &tab, 1) || strncmp( &line[location + word_length + 1], &newline, 1) ) )
				{
					if ( location < word_length || ( location > word_length && ( 0 == strncmp( &line[location - 1], &space, 1) || 0 == strncmp( &line[location - 1], &tab, 1) ) ) )
					{
						printf("%s", words[word_number]);
						printf("%s\t", line);
						word_number = WORD_COUNT + 1;
						location = read;
					}
				}
			}
		}
	}
	free(line);
	return;
}
/*
void libbsdl_preprocessor_getdata(char *line, struct bsdl_node *node)
{
	return;
}
*/
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

