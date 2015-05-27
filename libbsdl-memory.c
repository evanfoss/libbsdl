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

#include "libbsdl-memory.h"

#include <stdio.h>
#include <stdlib.h>

#include <glib.h>

#define LIBBSDL_PACKAGENAME_LENGTH 32

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
	char *attributes;
};

struct libbsdl_pins
{
	unsigned int number;
	char name[];
};

struct libbsdl_port
{
	unsigned int pincount;
	char name[LIBBSDL_PACKAGENAME_LENGTH];
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
	GList* preprocessed;
	char file_name[32];
	char entity_name[];
};


/*
 * the destroy of the h list is going to be done mostly via 
 * https://developer.gnome.org/glib/stable/glib-Singly-Linked-Lists.html#g-slist-free-full
 */

/* 
 *
 */
int libbsdl_open(void)
{
	struct libbsdl_node node1;
	node1.line_number = 1;
	GList* list = NULL;
	list = g_list_append(list, &node1);
	node1.line_number = 2;
	list = g_list_append(list, &node1);
	struct bsdl_node *node_from_list = g_list_first(list)->data;
	printf("%p", &node1);
	printf("\n");
	printf("%p", node_from_list);
	printf("\n");
	
	return 0;
}

int libbsdl_close(void)
{
	return 0;
}

#endif

