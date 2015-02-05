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
#include <stdlib.h>
#include "libbsdl.h"

#define SEVEN 7

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
	unsigned int location;
	while ((read = getline(&line, len, file)) != -1)
	{
		// loop from 0 to the end of line minus the length of the string.
		for (location = 0; location < read - 1; location++)
		{
			// at some point this should be changed to use strncasecmp(str1, str2, len) 
			// but I have never seen a file in the wild were this text is capitalized 
			// people seem to obey the conventions used everywhere else.
			// this is actually very ugly. I will clean it up later.
			if (line[location] == '-' && line[location + 1] == '-')
			{
				printf("comment found %s", line);
			} else
//			else if (line[location] =! ' ')
//			{
//				location == read;
//			}
			if (line[location] == 'e' && line[location + 1] == 'n' && line[location + 2] == 't' && line[location + 3] == 'i' && line[location + 4] == 't' && line[location + 5] == 'y')
			{
				printf("entity found %s", line);
				libbsdl_preprocessor_populate(file,len);
			} else
			if (line[location] == 'a' && line[location + 1] == 't')
			{
				printf("attribute found %s", line);
			} else
			if (line[location] == 'p' && line[location + 1] == 'o' && line[location + 2] == 'r' && line[location + 3] == 't')
			{
				printf("port found %s", line);
			}
			else if (line[location] != ' ')
			{
				printf("data found for last entry %s", line);
			}
			//printf("%d", strmcmp(line[location], "--", 2));
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


extern void libbsdl_print_comment_block()
{
	return;
}
*/
/*
void libbsdl_print_warnings(char *string[], unsigned short string_length)
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

struct bsdl_node *libbsdl_ll_new_node(struct bsdl_node *last)
{
	return;
}

struct bsdl_node *libbsdl_ll_new_subnode(struct bsdl_node *subhead)
{
	return;
}

void libbsdl_ll_del_node(struct bsdl_node *node)
{
	return;
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

/*
 * This is a node in the linked list used to store the preprocessed data.
 */
struct bsdl_node
{
	// obligatory
	struct bsdl_node *next;
	// The longest reserved word in the standard is 
	// COMPONENT_CONFORMANCE see page 265 of 
	// "The Boundary Scan Handbook" 2nd Ed.
	char *name;
	// The number of values is theoretically limitless.
	char *value;
	// if we have more than one value
	struct bsdl_node *sub;
};

#endif

