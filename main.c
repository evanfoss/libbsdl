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
	puts("Does the stdio work to talk to the display? (Basic sanity check) : YES\n");

	
	int bsdl_file;
	char *bsdl_file_content;
	char bsdl_file_name[] = "vaporware9000processor.bsdl";
	struct stat file_status_buffer;
	if((bsdl_file = open(bsdl_file_name, O_RDONLY)) < 0)
	{
		perror("open example bsdl file failed");
		exit(EXIT_FAILURE);
	}
	fstat(bsdl_file, &file_status_buffer);
	if((bsdl_file_content = mmap(0, file_status_buffer.st_size, PROT_READ, MAP_SHARED, bsdl_file, 0)) == MAP_FAILED)
	{     
		perror("memory mapping of bsdl file failed");
		exit(EXIT_FAILURE);
	}
	else
		puts("Beginning actual testing bsdl file opened\n");

	//I will change the shape of the libaries interface later.
//	libbsdl(*bsdl_file_content);
	puts("\n");

//	puts(*bsdl_file_content);

	close(bsdl_file);
	exit(0);
}
