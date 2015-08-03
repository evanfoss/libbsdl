/*
 * libbsdl-memory.c
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
#ifndef LIBBSDL_STRUCT_H_
#define LIBBSDL_STRUCT_H_

#define LIBBSDL_STRUCT_H_DEBUG

#include "libbsdl.h"
#include "libbsdl-memory.h"

#include <stdio.h>
#include <stdlib.h>

#include <glib.h>

#define LIBBSDL_NAMELENGTH 32

/*
 * This structure is for storing syntax issues found in processing the bsdl file.
 */
struct libbsdl_syntax
{
	unsigned int warnings_count;
	unsigned int errors_count;
	char *errors;
	char *warnings;
};

/*
 * This structure is for storing the information already post processed from the bsdl file.
 */
struct libbsdl_cache
{
	unsigned int pin_count;
	unsigned int ir_length;
	unsigned int attribute_count;
	char entity[LIBBSDL_NAMELENGTH];
};

/*
 *
 */
struct libbsdl_pins
{
	unsigned int number;
	char name[];
};

/* 
 * 
 */
struct libbsdl_port
{
	unsigned int pincount;
	char name[LIBBSDL_NAMELENGTH];
	struct libbsdl_pins pins[];
};

/* 
 * This structure is one of the nodes in the linked list of preprocessed bsdl file text.
 */
struct libbsdl_node
{
	unsigned int line_number;
	char content[3]; //fix me
};

/* 
 * This structure is the top level one held by the program calling this library. 
 * It is to be instantiated by a function in this library and destroyed by one.
 */
struct libbsdl_root
{
	struct libbsdl_syntax syntax; 
	struct libbsdl_cache cache;
	GList *preprocessed;
//	char file_name[LIBBSDL_NAMELENGTH];
//	char entity_name[LIBBSDL_NAMELENGTH];
};

#endif
