/* 
 * libbsdl.h
 * by evan foss
 * 2015.01.20
 *
 */

#ifndef LIBBSDL_H_
#define LIBBSDL_H_

#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * libbsdl commands
 * 	full text
 * 	warnnings
 * 	integrity check
 * 	device package
 * 	device pin count
 * 	full device id
 * 	device id
 * 	device version
 * 	device manufacture
 * 	(more to add later)
 *
 */
void libbsdl(char *bsdl_in, char *output, char *command);

#endif

