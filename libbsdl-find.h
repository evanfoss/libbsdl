/*
 * libbsdl-find.h
 * by Evan Foss
 * 2015.09.10
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
 * Copyright 2015.09.10 Evan Foss
 *
 */

#include <glib.h>

//I don't think I need these but it can't hurt to make the preprocessor earn it's keep
#ifndef LIBBSDL_FIND_H_
#define LIBBSDL_FIND_H_


GList *libbsdl_find_next_node(struct libbsdl_root *root, unsigned int max_depth, char *string_in);


#endif

