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
 *
 */

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "libbsdl.h"

int main(void)
{
	// open an example file
	FILE *bsdl_file;
	char bsdl_file_name[] = "vaporware9000processor.bsdl";
	struct stat file_status_buffer;
	bsdl_file = fopen(bsdl_file_name, "r");
	if (bsdl_file == NULL)
	{
		perror("open example bsdl file failed");
		exit(EXIT_FAILURE);
	}

	// space down a line
	puts("\n");

	// this is not what the interface to the library will look
	// like in the long run but i need to start somewhere
	libbsdl_initial_comments(bsdl_file);

	fclose(bsdl_file);
	exit(EXIT_SUCCESS);
}
