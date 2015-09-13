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

//#define LIBBSDL_C_DEBUG

#include <stdio.h>
/* When I first did this I was getting warnings from the compiler about 
 * incompatible implicite delarations. The strlen function in stdlib.h 
 * causes this. Please stick to the one in string.h
 */
#include <stdlib.h>
#include <string.h>
#include "libbsdl.h"
#include "libbsdl-memory.h"
#include "libbsdl-struct.h"

#define WORD_COUNT 31
#define WORD_LENGTH_MAX 10

// if the preprocessor is recursive but if it shall only be allowed 50 recursions (arbitrary but reasonable)
#define PREPROCESSOR_DEPTH 50

/* 
 *
 */
extern void libbsdl_preprocessor(FILE *file, struct libbsdl_root *root)
{

	size_t len = 0;
	// if the file we have been given is not there lets stop now.
	if (file == NULL)
	{
		return;
	}
	// create head node
	
	// call recursive function
	libbsdl_preprocessor_populate(file, &len, root);
	// is nead node address still a null pointer
	// if yes then the file is empty it does not
	// matter yes or know because we still return
	// the same way.
	
	return;
}

/*
 * 
 */
void libbsdl_preprocessor_populate(FILE *file, size_t *len, struct libbsdl_root *root)
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

//	struct libbsdl_node *node1;
//	node1 = (struct libbsdl_node *) malloc(sizeof(struct libbsdl_node));
	GList *sublist = NULL;
//	sublist1 = g_list_append(sublist1, node1);

	// look at the file line by line
	while ((read = getline(&line, len, file)) != -1)
	{
		location = 0;
		#ifdef LIBBSDL_C_DEBUG
		printf("\n");
		printf("%s", line);
		printf("\n");
		#endif
		sublist = libbsdl_line_preprocessor(read, line, count, location, &mode, &parentheses, depth, sublist);
		if ( ';' == mode )
		{
			mode = 'w';
			#ifndef LIBBSDL_C_DEBUG
			g_list_first(sublist);
			(*root).preprocessed = g_list_append((*root).preprocessed, sublist);
			#endif
			sublist = NULL;
			#ifdef LIBBSDL_C_DEBUG
			printf("\nNew Sublist\n");
			#endif
		}
		count++;
	}
	#ifdef LIBBSDL_C_DEBUG
	printf("\n");
	printf("lines %d", count);
	printf("\n\n");
	#endif
	free(line);
	return;
}

/* 
 * This function really does not read a whole line. What it does is recrusvily process a line one segment at a time. 
 * 
 *
 *
 */
GList *libbsdl_line_preprocessor(ssize_t line_length, char line[], unsigned int line_number, unsigned int location, char *mode, int *parentheses, unsigned int depth, GList *list) //, char *request_vnode)
{
	// the number corsponding to the word we are looking for right now
	unsigned int word_number = 0;
	// the words we have to look for *NEVER CHANGE THE ORDER* only add onto the end of this list if you must
	char words[WORD_COUNT][WORD_LENGTH_MAX] = {"port\0", "string\0", "of\0", "is\0", "signal\0", "vector\0", "entity\0", "generic\0", "constant\0", "use\0", "attribute\0", "type\0", "subtype\0", "package\0", "sll\0", "srl\0", "sla\0", "sra\0", "rol\0", "ror\0", "and\0", "or\0", "nand\0", "nor\0", "xnor\0", "xor\0", "not\0", "abs\0", "mod\0", "rem\0", "end\0"};
	unsigned int marker = 0;
	struct libbsdl_node *node;
	// for testing purposes
	char out[line_length];
	// fail if we exit after an arbitrarily excessive depth
	if ( depth > PREPROCESSOR_DEPTH )
	{
		// i should really add an assertion here
		return NULL;
	}
	location = libbsdl_end_of_whitespace(line, location);
	// make sure we have not hit the end of the line (terminal case for recursion)
	if ( line_length <= location )
	{
		return list;
	}

	marker = location;
	marker = libbsdl_preprocessor_specialcharid(line, location, mode, parentheses);
	if ( 'p' == *mode )
	{
		// I need to work out how the end is found.
		//parentheses =+ libbsdl_parentheses_ballance(line, location, end);
		if ( 0 == (*parentheses) )
		{
			#ifdef LIBBSDL_C_DEBUG
			printf(" exiting port mode\n");
			#endif
			*mode = 'w';
		}
	}
	if ( marker == location )
	{
		for (word_number = 0; word_number < WORD_COUNT; word_number++)	
		{	
			if ( 1 == libbsdl_offset_is_word(line, words[word_number], location))
			{
				#ifdef LIBBSDL_C_DEBUG
				printf(" found word %s", words[word_number]);
				printf("\n");
				#endif
				location += strlen(words[word_number]);
				if ( word_number == 0)
				{	//to be enabled later
					*mode = 'p';
					#ifdef LIBBSDL_C_DEBUG
					printf(" found a port changing modes \n");
					#endif
				} else 
				if ( word_number == 6 && depth == 0 )
				{
					*mode = ';';
				}
				depth++;
				#ifndef LIBBSDL_C_DEBUG
				node = libbsdl_catchnode(line_number, words[word_number]);
				list = g_list_append(list, node);
				#endif
				return libbsdl_line_preprocessor(line_length, line, line_number, location, mode, parentheses, depth, list);
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
	#ifdef LIBBSDL_C_DEBUG
	printf(" output : %s", out);
	printf("\n");
	#endif
	location = marker;
	depth++;
	#ifndef LIBBSDL_C_DEBUG
	node = libbsdl_catchnode(line_number, out);
	list = g_list_append(list, node);
	#endif
	return libbsdl_line_preprocessor(line_length, line, line_number, location, mode, parentheses, depth, list);
}

int libbsdl_preprocessor_specialcharid(char line[], unsigned int location, char *mode, int *parentheses)
{
	int marker;
	marker = location;
	switch ( line[location] )
	{
		case '-':
			if ( '-' == line[location + 1] )
			{
				#ifdef LIBBSDL_C_DEBUG
				printf("\n");
				printf(" comment detected\n");
				#endif
				marker = strlen(line);
				if ('\n' == line[marker - 1])
				{
					marker--;
				}
			} else
			{
				marker++;
				#ifdef LIBBSDL_C_DEBUG
				printf(" subtraction\n");
				#endif
			}
			break;
		case '+':
			marker++;
			#ifdef LIBBSDL_C_DEBUG
			printf(" addition\n");
			#endif
			break;
		case '"':
			*mode = '"';
			// look ahead for second quote mark and copy bulk then go to that location + 1
			marker++;
			marker = libbsdl_line_search_char(line, marker, '"');
			#ifdef LIBBSDL_C_DEBUG
			printf(" location %d", location);
			printf(" string open\n");
			printf(" location %d", marker);
			printf(" string closed\n");
			#endif
			marker++;
			break;
		case ';':
			#ifdef LIBBSDL_C_DEBUG
			printf(" ; (end of words)\n");
			#endif
			if ( 'p' == *mode && 0 != *parentheses )
			{
				#ifdef LIBBSDL_C_DEBUG
				printf("need new vertical subnode\n");
				#endif
			} else
			{
				*mode = ';';
			}
			marker++;
			break;
		case ':':
			if ( '=' == line[location + 1] )
			{
				#ifdef LIBBSDL_C_DEBUG
				printf(" := (equivilence) \n");
				#endif
				marker += 2;
			} else
			{
				marker++;
				#ifdef LIBBSDL_C_DEBUG
				printf(" : (assignment of)\n");
				#endif
			}
			break;
		case '=':
			if ( '>' == line[location + 1] )
			{
				marker += 2;
				#ifdef LIBBSDL_C_DEBUG
				printf(" >= more than or equal too\n");
				#endif
			} else
			if ( '<' == line[location + 1] )
			{
				marker += 2;
				#ifdef LIBBSDL_C_DEBUG
				printf(" <= less than or equal too\n");
				#endif
			} else
			{
				marker++;
				#ifdef LIBBSDL_C_DEBUG
				printf(" = equal too\n");
				#endif
			}
			break;
		case '(':
			marker++;
			(*parentheses)++;
			#ifdef LIBBSDL_C_DEBUG
			printf(" ( grouping started \n");
			printf(" parentheses count %d", *parentheses);
			printf("\n");
			#endif
			break;
		case ')':
			marker++;
			(*parentheses)--;
			#ifdef LIBBSDL_C_DEBUG
			printf(" ) grouping ended \n");
			printf(" parentheses count %d", *parentheses);
			printf("\n");
			#endif
			break;
		case ',':
			marker++;
			#ifdef LIBBSDL_C_DEBUG
			printf(" , another value listed\n");
			#endif
			break;
		case '\\':
			if ( '=' == line[location + 1] )
			{
				marker += 2;
				#ifdef LIBBSDL_C_DEBUG
				printf(" \\= not equal too\n");
				#endif
			} else
			{
				marker++;
				#ifdef LIBBSDL_C_DEBUG
				printf(" \\ divided by\n");
				#endif
			}
			break;
		case '\'':
			if ( '\\' == line[location + 1] && '\'' == line[location + 3] )
			{
				marker += 4;
				#ifdef LIBBSDL_C_DEBUG
				printf(" ascii character (special) found\n");
				#endif
			} else
			if ( '\\' != line[location + 1] && '\'' == line[location + 2] )
			{
				marker += 3;
				#ifdef LIBBSDL_C_DEBUG
				printf(" ascii character value found\n");
				#endif
			} else
			{
				marker++;
				#ifdef LIBBSDL_C_DEBUG
				printf(" syntax error\n");
				#endif
			}
			break;
		case '*':
			if ( '*' == line[location + 1])
			{
				marker += 2;
				#ifdef LIBBSDL_C_DEBUG
				printf(" ** exponentiation \n");
				#endif
			} else
			{
				marker++;
				#ifdef LIBBSDL_C_DEBUG
				printf(" * multiplication \n");
				#endif
			}
			break;
		case '&':
			if ( '"' == *mode )
			{
				marker++;
				#ifdef LIBBSDL_C_DEBUG
				printf(" more string left\nneed new vertical subnode \n");
				#endif
			} else
			{
				marker++;
				#ifdef LIBBSDL_C_DEBUG
				printf(" concatenation \n");
				#endif
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
	if ( line[number] == ascii_space || line[number] == ascii_tab  || line[number] == ascii_terminate || line[number] == ascii_newline )
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

#endif

