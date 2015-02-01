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

// the most pins I could find on a chip in digikey was a 40x40 grid
#define PIN_NAME_LENGTH 6;
// max length of the idcode in bits
#define MAX_IDCODE_LENGTH 32;


/*
 * libbsdl commands listed by what they should return. 
 * Some of this may seem unneeded but not all bsdl files are complaint with IEEE specification.
 * 	full text (text)
 * 	design warnings (text)
 * 	syntax clean (y/n)
 * 	device package (text)
 * 	device pin count (text)
 * 	full device id (text)
 * 	device id (text)
 * 	device version (text)
 * 	device manufacture (text)
 * 	device TAP clock speed in hz (unsigned int)
 *	device TAP clock rising/falling/dual (text)
 *	device TAP pins (structure)
 * 	device opcode count (unsigned int)
 * 	device opcode list (text)
 * 	device opcode length (unsigned int)
 * 	(more to add later)
 *
 */

//void libbsdl(char *bsdl_in, char *output, char *command);

void libbsdl_max_str_length(char *textin);

struct libbsdl_standards
{
	// which IEEE STD are we using?
	// STD_1149_1_2001 or similar
//	char conformance[];
	// which library or libraries are we using to define the cells?
//	char use_std[];
};

struct libbsdl_opcodes
{
	// how many bits to the opcode
	unsigned int length;
	// how many opcodes are we dealing with
	unsigned int count;
	// pointer to arry of opcodes;
	// *****************************************Fill this in later***********************************
};

struct libbsdl_idcode
{
	// the idcode has to be in characters because it has 0, 1, and X
//	char full[];
	// how long is the id code (IEEE STD says 32 bits but lets export that)
	unsigned short length;
	// this should be the version number
//	char field1_guessversion[];
	// this should be the part number
//	char field2_guesspartnum[];
	// this should be the manufacture number
//	char field3_guessmfg[];
	// this should always be 1 because of IEEE 1149.1
//	char field4_ieeespec;

};

struct libbsdl_package
{
	// pointer to the selected package (defaults to package 1)
//	char *selection[];
	// how many packages do we have to pick from
	unsigned char number_of_packages;
//	char package_names[];
};

struct libbsdl_tap
{
	/* I used to attribute some significance to the vdhl attributes
	 * saying that each of the TAP pins are true. Now I know that 
	 * is just for compliance with the vhdl std.
	 * pg 58 of The Boundary-Scan Handbook 2nd Edition
	 
	// tap clock speed in Hz
	unsigned long speed;
	// do we have a trst pin on this chips tap?
	bool trst_exists;
	// low or BOTH for the tap clock edge timing?
	char[4] tck_clocking; 
	// where are the pins for the tap?
*///	char tdi_pin[PIN_NAME_LENGTH];
//	char[PIN_NAME_LENGTH] tdo_pin;
//	char[PIN_NAME_LENGTH] tms_pin;
//	char[PIN_NAME_LENGTH] tck_pin;
//	char[PIN_NAME_LENGTH] trst_pin;
};

void libbsdl_proprocessor(void);

#endif

