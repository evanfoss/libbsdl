# libbsdl
# root Makefile
# By Evan Foss
# Date 2015.01.19
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
#
# Copyright 2015.02.02 Evan Foss
#

CC := gcc
SRC_FILES = \
	libbsdl.c \
	libbsdl.h \
	libbsdl-memory.c \
	libbsdl-memory.h

SRC_FILES_TEST_PRE = test-preprocessor.c
SRC_FILES_TEST_MEM = test-memory.c

all: libbsdl test


libbsdl:
	echo 'building lib bsdl'
	$(CC) -fPIC -c $(SRC_FILES) -o libbsdl.o
	$(CC) -g -shared  -Wl, -soname, libbsdl.so -o libbsdl.so libbsdl.o -lc

test:
#A total shakedown test should go here later.

testpre:
	clear
	echo 'testing lib bsdl'
	$(CC) -Wall $(SRC_FILES_TEST_PRE) $(SRC_FILES) `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -o test.bin 
	#valgrind --leak-check=full --show-leak-kinds=all ./test.bin
	./test.bin
	rm test.bin

testmem:
	clear
	$(CC) -Wall $(SRC_FILES_TEST_MEM) $(SRC_FILES) `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0` -o test.bin
	valgrind --leak-check=full --show-leak-kinds=all ./test.bin
	rm test.bin

clean:
	echo 'clean up.'
	rm test.bin

fetchbsdl: #This does not quite work yet but I will lick it later. The point is just to have the files now for unit testing
	cd test
#	wget -c http://www.microsemi.com/document-portal/doc_download/134219-m2gl005s-vf256-bsdl
#	wget -c http://www.analog.com/static/imported-files/bsdl_files/bsdl_21060_cqfp_cw.txt
#	wget -c https://www-01.ibm.com/chips/techlib/techlib.nsf/techdocs/519ADC0C9F7692708725716B00600833/$file/cpc945.bsdl
#	wget -c https://www-01.ibm.com/chips/techlib/techlib.nsf/techdocs/519ADC0C9F7692708725716B00600833/$file/IBMDFT_1149_1_1998_V5
	wget -c http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33FJ128GP206.bsd
	wget -c http://ww1.microchip.com/downloads/en/DeviceDoc/PIC24FJ128GA006.bsd
	wget -c ftp://ftp.altera.com/outgoing/download/bsdl/EP4CE22E22.bsd
	wget -c ftp://ftp.altera.com/outgoing/download/bsdl/EP4CE6E22.bsd
	wget -c ftp://ftp.altera.com/outgoing/download/bsdl/3064al44.bsd
	wget -c ftp://ftp.altera.com/outgoing/download/bsdl/3128at144_1532.bsd
	#altera has stuff sorted by ieee standard number!
	wget -c http://www.renesas.eu/support/downloads/download_results/C2016301-C2016400/sh_bsdl_hd6417709s_bsdl_csp_7709s.jsp
	wget -c http://www.atmel.com/images/UC3A0_A1_bsdl_files.zip


