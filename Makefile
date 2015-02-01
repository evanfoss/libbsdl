# libbsdl
# root Makefile
# By Evan Foss
# Date 2015.01.19

CC := gcc
SRC_FILES = \
	libbsdl.c \
	libbsdl.h

SRC_FILES_TEST = main.c 

all: libbsdl test


libbsdl:
	echo 'building lib bsdl'
	$(CC) -fPIC -c $(SRC_FILES) -o libbsdl.o
	$(CC) -g -shared  -Wl, -soname, libbsdl.so -o libbsdl.so libbsdl.o -lc

test:
	clear
	echo 'testing lib bsdl'
	$(CC) $(SRC_FILES_TEST) $(SRC_FILES) -o test.bin
	./test.bin
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


