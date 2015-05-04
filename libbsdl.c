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

// if the preprocessor is recursive but if it shall only be allowed 50 recursions (arbitrary but reasonable)
#define PREPROCESSOR_DEPTH 50

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
	int parentheses = 0;
	// look at the file line by line
	while ((read = getline(&line, len, file)) != -1)
	{
		location = 0;
		printf("\n");
		printf("%s", line);
		printf("\n");
//		printf(" mode %c", *mode);
//		printf("\n");
		libbsdl_line_preprocessor(read, line, count, location, &mode, &parentheses, depth);
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
int libbsdl_line_preprocessor(ssize_t line_length, char line[], unsigned int line_number, unsigned int location, char *mode, int *parentheses, unsigned int depth) //, char *request_vnode)
{
	// the number corsponding to the word we are looking for right now
	unsigned int word_number = 0;
	// the words we have to look for *NEVER CHANGE THE ORDER* only add onto the end of this list if you must
	char words[WORD_COUNT][WORD_LENGTH_MAX] = {"port\0", "string\0", "of\0", "is\0", "signal\0", "vector\0", "entity\0", "generic\0", "constant\0", "use\0", "attribute\0", "type\0", "subtype\0", "package\0", "end\0"};
	unsigned int marker = 0;
	// for testing purposes
	char out[50];
	// fail if we exit after an arbitrarily excessive depth
	if ( depth > PREPROCESSOR_DEPTH )
	{
		return -1;
	}
	location = libbsdl_end_of_whitespace(line, location);
	// make sure we have not hit the end of the line (terminal case for recursion)
	if ( line_length <= location )
	{
		return 0;
	}
	marker = location;
	marker = libbsdl_preprocessor_specialcharid(line, location, mode, parentheses);
	if ( 'p' == *mode )
	{
		// I need to work out how the end is found.
		//parentheses =+ libbsdl_parentheses_ballance(line, location, end);
		if ( 0 == (*parentheses) )
		{
			printf(" exiting port mode\n");
			(*mode) = 'w';
		}
	} else
	if ( 'c' == *mode )
	{
		*mode = 'w';
		return 0;
	} else
	if ( marker == location )
	{
		for (word_number = 0; word_number < WORD_COUNT; word_number++)	
		{	
			if ( 1 == libbsdl_offset_is_word(line, words[word_number], location))
			{
				printf(" found word %s", words[word_number]);
				printf("\n");
				location += strlen(words[word_number]);
				if ( word_number == 0)
				{	//to be enabled later
					*mode = 'p';
					printf(" found a port changing modes \n");
				}
				depth++;
				return libbsdl_line_preprocessor(line_length, line, line_number, location, mode, parentheses, depth);
			}
		}
		// ok if we are down here it is not a symbol, comment or in the word list
		marker = libbsdl_end_of_word(line, location);
		if ( location != ( marker + 1 ))
		{
//			printf(" is this many characters long %d", (marker - location + 1));
//			printf("\n");
			marker++;
		} else
		{	// odds are high we just hit a symbol that is not supposed to be here but lets catch it any way
			return 0;
		}
	}
	// after i fix the code to write what it finds out this next line should be replaced with skipping the found texts length
	strncpy(out, &(line[location]), (marker - location ));
	out[( marker - location  )] = '\0';
	printf(" output : %s", out);
	printf("\n");
	location = marker;
	depth++;
	return libbsdl_line_preprocessor(line_length, line, line_number, location, mode, parentheses, depth);
}

int libbsdl_preprocessor_specialcharid(char line[], int location, char *mode, int *parentheses)
{
	int marker;
	marker = location;
	switch ( line[location] )
	{
		case '-':
			if ( '-' == line[location + 1] )
			{
				printf("\n");
				printf(" comment detected\n");
				*mode = 'c';
			} else
			{
				marker++;
				printf(" subtraction\n");
			}
			break;
		case '+':
			marker++;
			printf(" addition\n");
			break;
		case '"':
			*mode = '"';
			printf(" string open\n");
			// look ahead for second quote mark and copy bulk then go to that location + 1
			marker++;
			marker = libbsdl_line_search_char(line, marker, '"');
			printf(" location %d", marker);
			printf(" string closed\n");
			marker++;
			break;
		case ';':
			printf(" ; (end of words)\n");
			if ( 'p' == *mode && 0 != *parentheses )
			{
				printf("need new vertical subnode\n");
			} else
			{
				*mode = 'w';
			}
			marker++;
			break;
		case ':':
			if ( '=' == line[location + 1] )
			{
				printf(" := (equivilence) \n");
				marker += 2;
			} else
			{
				marker++;
				printf(" : (assignment of)\n");
			}
			break;
		case '=':
			if ( '>' == line[location + 1] )
			{
				marker += 2;
				printf(" >= more than or equal too\n");
			} else
			if ( '<' == line[location + 1] )
			{
				marker += 2;
				printf(" <= less than or equal too\n");
			} else
			{
				marker++;
				printf(" = equal too\n");
			}
			break;
		case '(':
			marker++;
			(*parentheses)++;
			printf(" ( grouping started \n");
			printf(" parentheses count %d", *parentheses);
			printf("\n");
			break;
		case ')':
			marker++;
			(*parentheses)--;
			printf(" ) grouping ended \n");
			printf(" parentheses count %d", *parentheses);
			printf("\n");
			break;
		case ',':
			marker++;
			printf(" , another value listed\n");
			break;
		case '\\':
			if ( '=' == line[location + 1] )
			{
				marker += 2;
				printf(" \\= not equal too\n");
			} else
			{
				marker++;
				printf(" \\ divided by\n");
			}
			break;
		case '\'':
			if ( '\\' == line[location + 1] && '\'' == line[location + 3] )
			{
				marker += 4;
				printf(" ascii character (special) found\n");
			} else
			if ( '\\' != line[location + 1] && '\'' == line[location + 2] )
			{
				marker += 3;
				printf(" ascii character value found\n");
			} else
			{
				marker++;
				printf(" syntax error\n");
			}
			break;
		case '*':
			if ( '*' == line[location + 1])
			{
				marker += 2;
				printf(" ** exponentiation \n");
			} else
			{
				marker++;
				printf(" * multiplication \n");
			}
			break;
		case '&':
			if ( '"' == *mode )
			{
				marker++;
				printf(" more string left\n");
			//hold depth
			} else
			{
				marker++;
				printf(" concatenation \n");
			}
			break;
		default:
			marker = location;
			break;
	}
	// it is technically impossible to get down here but I feel safer with this.
	return marker;
}

int libbsdl_parentheses_ballance(char line[], int offset, int end)
{
	int count = 0;
	unsigned int length;
	int location;
	length = strlen(line);
	if ( 0 >= length || 0 >= offset )
	{
		return 0;
	}
	for (location = offset; length >= location; location++)
	{
		
		if ( '(' == line[location] )
		{
			count++;
		} else
		if ( ')' == line[location] )
		{
			count--;
		}
	}
	return count;
}

int libbasl_comment_offset(char line[], int offset)
{
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
	if ( offset > (word_length - 1) && ( 1 != libbsdl_is_whitespace(line, (offset - 1) ) ) )
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
 * This function returns the location for the end of the word you are on.
 *
 */
int libbsdl_end_of_word(char line[], int offset)
{
	unsigned int length;
	length = strlen(line);
	while ( ( offset <= length ) && ( ( 'A' <= (line[offset]) && 'Z' >= (line[offset]) ) || ( 'a' <= (line[offset]) && 'z' >= (line[offset]) ) || ( '0' <= (line[offset]) && '9' >= (line[offset]) ) || ( '_' == (line[offset])) || ( '.' == (line[offset])) ) )
	{
		offset++;
	}
	offset--;
	return offset;
}

/*
char libbsdl_offset_is_letter()

*/

/*
 * Skip white space. It pretty much is what it says.
 *
 */
int libbsdl_end_of_whitespace(char line[], unsigned int number)
{
	unsigned int length;
	length = strlen(line);
	while ( ( number < length ) && ( 0 < libbsdl_is_whitespace(line, number) ) )
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
	if ( line[number] == ascii_space || line[number] == ascii_tab  || line[number] == ascii_newline || line[number] == ascii_terminate )
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

