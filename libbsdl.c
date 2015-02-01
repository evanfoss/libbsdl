/*
 * libbsdl.c
 * by Evan Foss
 * 2015.01.20
 */

//I don't think I need these but it can't hurt to make the preprocessor earn it's keep
#ifndef LIBBSDL_C_
#define LIBBSDL_C_

#include <stdio.h>
#include <stdlib.h>
#include "libbsdl.h"

/*
extern void libbsdl_preprocessor(void)
{
	return;
}
*/

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

extern unsigned int libbsdl_initial_comments(FILE *file)
{

	unsigned int location = 0;
	// loop from 0 to the end of line minus the length of the string.
	for (location = 0; location < string_length; location++)
	{
		// if true then we found the comment
		if (string[0] == "--")
		{
			// printf("Retrieved line of length %zu :\n", read);
			printf("%s", *string);
			// this will terminate the loop
			string_length = location;
		}
	}
	return location;
}
*/
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

