/*
 * main.c
 * for testing libbsdl
 * by Evan Foss
 * Date 2015.01.19
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
