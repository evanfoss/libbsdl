/*
 * main.c
 * for testing libbsdl
 * by Evan Foss
 * Date 2015.01.19
 */

#include<stdio.h>
#include<unistd.h>
#include"libbsdl.h"

int main(void)
{
	puts("Does the stdio work to talk to the display? (Basic sanity check) : YES\n");

	int bsdl_file;
	char bsdl_file[] = "vaporware9000processor.bsdl";

	struct = stat statbuf;

	if((fd = open(argv[1], O_RDONLY)) < 0)
	{
		perror("open example bsdl file failed");
		exit(EXIT_FAILURE);
	}
	fstat(fd, &statbuf);

	if((src = mmap(0, statbuf.st_size, PROT_READ,
		MAP_SHARED, fd, 0)) == MAP_FAILED)
	{
		perror("memory mapping of bsdl file failed");
		exit(EXIT_FAILURE);
	}
	


	close(bsdl_file);
	exit(0);
}

