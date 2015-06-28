/*
 * main.c
 * for testing libbsdl
 * by Evan Foss
 * Date 2015.01.19
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
 */

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "libbsdl.h"

int main(void)
{
	// open an example file
	FILE *bsdl_file;
	char bsdl_file_name[] = "vaporware9000processor.bsdl";
	printf("*** open the file ***\n");
	bsdl_file = fopen(bsdl_file_name, "r");
	if (bsdl_file == NULL)
	{
		perror("open example bsdl file failed");
		exit(EXIT_FAILURE);
	}

	// grab some memory for the library to use
	struct libbsdl_root *bsdl;
	bsdl = libbsdl_open();
	if (bsdl == NULL)
	{
		perror("out of memory!?\n");
		exit(EXIT_FAILURE);
	}

	// preprocess the library
	printf("*** test preprocessor ***\n");
//	libbsdl_preprocessor(bsdl_file, bsdl);
	fclose(bsdl_file);

	// more tbd

	// free the memeory the library to use
	printf("*** now we just have to exit cleanly ***\n");
	libbsdl_close(bsdl);
	libbsdl_memtest();
	exit(EXIT_SUCCESS);
}
