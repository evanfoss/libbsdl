/* 
 * libbsdl.h
 * by evan foss
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

// this should return a pointr to the initial comments in the bsdl file
// technically like all comments they are optional but no file i have 
// ever seen or heard of is with out them.
extern void libbsdl_initial_comments(FILE *file);

extern void libbsdl_preprocessor(FILE *file);
void libbsdl_preprocessor_populate(FILE *file, size_t *len);

//void libbsdl_print_warnings(char *string[], unsigned short string_length);

#endif

