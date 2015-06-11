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
#ifndef LIBBSDL_MEMORY_C_
#define LIBBSDL_MEMORY_C_

#define LIBBSDL_MEMORY_C_DEBUG

#include "libbsdl-memory.h"

#include <stdio.h>
#include <stdlib.h>

#include <glib.h>

#define LIBBSDL_NAMELENGTH 32

struct libbsdl_syntax
{
	unsigned int warnings_count;
	unsigned int errors_count;
	char *errors;
	char *warnings;
};

struct libbsdl_cache
{
	unsigned int pin_count;
	unsigned int ir_length;
	unsigned int attribute_count;
	char entity[LIBBSDL_NAMELENGTH];
	char *attributes[];
};

struct libbsdl_pins
{
	unsigned int number;
	char name[];
};

struct libbsdl_port
{
	unsigned int pincount;
	char name[LIBBSDL_NAMELENGTH];
	struct libbsdl_pins pins[];
};

struct libbsdl_node
{
	unsigned int line_number;
	char content[];
};

struct libbsdl_root
{
	struct libbsdl_syntax syntax; 
	struct libbsdl_cache cache;
	GList *preprocessed;
	char file_name[LIBBSDL_NAMELENGTH];
	char entity_name[LIBBSDL_NAMELENGTH];
};


/*
 * the destroy of the h list is going to be done mostly via 
 * https://developer.gnome.org/glib/stable/glib-Singly-Linked-Lists.html#g-slist-free-full
 */

/* 
 *
 */
struct libbsdl_root *libbsdl_open(void)
{
	struct libbsdl_root *root;
	root = (struct libbsdl_root*) malloc(sizeof(struct libbsdl_root));
	(*root).preprocessed = NULL;
	#ifdef LIBBSDL_MEMORY_C_DEBUG
	printf("libbsdl-memory: Root memory structure created.\n");
	#endif

	struct libbsdl_node *node1;
	node1 = (struct libbsdl_node*) malloc(sizeof(struct libbsdl_node));

	GList *sublist1 = NULL;
	sublist1 = g_list_append(sublist1, node1);

	(*root).preprocessed = g_list_append((*root).preprocessed, sublist1);
	return root;
}

void libbsdl_close(struct libbsdl_root *root)
{
	g_list_foreach((*root).preprocessed, (GFunc)g_free , NULL);
	g_list_free((*root).preprocessed);
	free(root);
	return;
}

#endif

