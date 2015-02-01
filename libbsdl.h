/* 
 * libbsdl.h
 * by evan foss
 * 2015.01.20
 *
 */

#ifndef LIBBSDL_H_
#define LIBBSDL_H_

#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

// the most pins I could find on a chip in digikey was a 40x40 grid
#define PIN_NAME_LENGTH 6;
// max length of the idcode in bits
#define MAX_IDCODE_LENGTH 32;


/*
 * libbsdl commands listed by what they should return. 
 * Some of this may seem unneeded but not all bsdl files are complaint with IEEE specification.
 * 	full text (text)
 * 	design warnings (text)
 * 	syntax clean (y/n)
 * 	device package (text)
 * 	device pin count (text)
 * 	full device id (text)
 * 	device id (text)
 * 	device version (text)
 * 	device manufacture (text)
 * 	device TAP clock speed in hz (unsigned int)
 *	device TAP clock rising/falling/dual (text)
 *	device TAP pins (structure)
 * 	device opcode count (unsigned int)
 * 	device opcode list (text)
 * 	device opcode length (unsigned int)
 * 	(more to add later)
 *
 */

//extern void libbsdl_preprocessor(void);
/*
extern unsigned int libbsdl_initial_comments(FILE *file);

void libbsdl_print_warnings(char *string[], unsigned short string_length);
*/
#endif

