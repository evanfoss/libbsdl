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
#include "libbsdl-struct.h"

#include <stdio.h>
#include <stdlib.h>

#include <glib.h>

/* 
 * This function instantiates the top level memory structure used by this library.
 */
struct libbsdl_root *libbsdl_open(void)
{
	struct libbsdl_root *root;
	root = (struct libbsdl_root*) malloc(sizeof(struct libbsdl_root));
	(*root).preprocessed = NULL;
	(*root).syntax.warnings = NULL;
	(*root).syntax.errors = NULL;
	return root;
}


#ifdef LIBBSDL_MEMORY_C_DEBUG
void libbsdl_memtest(void)
{
	// create a root structure to play with
	struct libbsdl_root *root;
	root = libbsdl_open();
	// test the linked list handling
	printf("libbsdl-memory: Root memory structure created.\n");
	struct libbsdl_node *node1;
	node1 = (struct libbsdl_node*) malloc(sizeof(struct libbsdl_node));
	printf("node 1%p", node1);
	printf("\n");
	GList *sublist1 = NULL;
	sublist1 = g_list_append(sublist1, node1);
	printf("sublist 1%p", sublist1);
	printf("\n");
	(*root).preprocessed = g_list_append((*root).preprocessed, sublist1);
	// lets look at that
	libbsdl_print(root);
	// test the handful of strings that are reached via pointer
	printf("test the handling of syntax error and warning storage. (sub struct pointers)\n");
	(*root).syntax.errors = (char *) malloc(6 * sizeof(char));
	(*root).syntax.warnings = (char *) malloc(6 * sizeof(char));
	//(*(*root).syntax.warnings) = "yes.\0";
	//printf("%s", *(*root).syntax.warnings);
	printf("test done free up all our memory.\n");
	// clean up behind ourselves
	libbsdl_close(root);
	return;
}
#endif

/* 
 * This function closes the data structure used by libbsdl freeing all it's used memory.
 */
void libbsdl_close(struct libbsdl_root *root)
{
	g_list_first((*root).preprocessed);
	// first we free each of the nodes in the horizontal lists
	g_list_foreach((*root).preprocessed, (GFunc)libbsdl_closeh , NULL);
	// then we free the vertical list
	g_list_free((*root).preprocessed);
	// then we free everything else in the root structure
	free((*root).syntax.warnings);
	free((*root).syntax.errors);
	free(root);
	return;
}

/* 
 * This function closes the linked list. 
 * The prototype for this function is defined by glib.
 * For more on that look at the following two links.
 * glib refrence.
 * https://developer.gnome.org/glib/stable/glib-Doubly-Linked-Lists.html
 * 3rd party description.
 * http://www.mega-nerd.com/erikd/Blog/CodeHacking/g_list_foreach.html
 */
void libbsdl_closeh(gpointer data, gpointer user_data)
{
	g_list_first(data);
	g_list_foreach(data, (GFunc)g_free , NULL);
	free(data);
	return;
}

void libbsdl_print(struct libbsdl_root *root)
{
	printf("printing list\n");
	g_list_first((*root).preprocessed);
	g_list_foreach((*root).preprocessed, (GFunc)libbsdl_printh, NULL);
	return;
}

void libbsdl_printh(gpointer data, gpointer user_data)
{
	printf("sublist\n");
	g_list_first(data);
	g_list_foreach(data, (GFunc)libbsdl_printnode, NULL);
	return;
}

void libbsdl_printnode(gpointer data, gpointer user_data)
{
	printf("node \n");
	return;
}

#endif

