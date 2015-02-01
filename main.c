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

	// this will later to migrated to other areas
	// prep to use getline
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	// loop and to through all the lines
	while ((read = getline(&line, &len, bsdl_file)) != -1)
	{
		// if this test here works I should get a display of the line number 
		// and text of all the lines that start with text
		if (line[0] == '-' & line[1] == '-')
		{
			printf("Retrieved line of length %zu :\n", read);
			printf("%s", line);
		}
	}
	free(line);

	fclose(bsdl_file);
	exit(EXIT_SUCCESS);
}
