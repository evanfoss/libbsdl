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
#include "libbsdl-memory.h"

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

extern void libbsdl_preprocessor(FILE *file, struct libbsdl_root *root);
// void libbsdl_preprocessor_findtype(char *line, );
void libbsdl_preprocessor_populate(FILE *file, size_t *len, struct libbsdl_root *root);
//void libbsdl_preprocessor_getdata(char *line, struct bsdl_node *node);
int libbsdl_line_preprocessor(ssize_t line_length, char line[], unsigned int line_number, unsigned int location, char *mode, int *parentheses, unsigned int depth);

int libbsdl_preprocessor_specialcharid(char line[], unsigned int location, char *mode, int *parenteses);

int libbsdl_offset_is_word(char line[], char word[], unsigned int offset);

int libbsdl_end_of_word(char line[], int offset);
int libbsdl_end_of_whitespace(char line[], unsigned int number);
int libbsdl_is_whitespace(char line[], unsigned int number);
int libbsdl_offset_is_word(char line[], char word[], unsigned int offset);
int libbsdl_line_search_char(char line[], unsigned int offset, char looking_for);

#endif

