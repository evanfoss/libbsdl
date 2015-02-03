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
	// what kind of line are we in? c = comment e = entity a = attribute and etc.
	char flag = 'b';
	while ((read = getline(&line, len, file)) != -1)
	{
		// loop from 0 to the end of line minus the length of the string.
		for (location = 0; location < read - 1; location++)
		{
		if (flag == 'b')
		{
			// if true then we found the comment
			if (line[location] == '-' && line[location + 1] == '-')
			{
				flag = 'c';
				printf("comment found %s", line);
			} else
//			else if (line[location] =! ' ')
//			{
//				location == read;
//			}
			if (line[location] == 'e' && line[location + 1] == 'n' && line[location + 2] == 't' && line[location + 3] == 'i' && line[location + 4] == 't' && line[location + 5] == 'y')
			{
				flag = 'e';	
				printf("entity found %s", line);
				libbsdl_preprocessor_populate(file,len);
			} else
			if (line[location] == 'a' && line[location + 1] == 't')
			{
				flag = 'a';
				printf("attribute found %s", line);
			} else
			if (line[location] == 'p' && line[location + 1] == 'o' && line[location + 2] == 'r' && line[location + 3] == 't')
			{
				flag = 'p';
				printf("port found %s", line);
			}
			else if (flag != 'b' && line[location] != ' ')
			{
				flag = 'd';
				printf("data found for last entry %s", line);
			}
//			printf("%d", strcmp(line[location], "--", 2));
		}
		}
		flag = 'b';
	}
	free(line);
	return;
}


/*
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

void libbsdl_ll_new_entry()
{
	return;
}

void libbsdl_ll_new_value()
{
	return;
}

void libbsdl_ll_new_attribute()
{
	return;
}

void libbsdl_ll_new_comment()
{
	return;
}

void libbsdl_ll_del_list()
{
	return;
}
*/
#endif

