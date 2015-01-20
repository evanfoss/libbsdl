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
	cd src
	$(CC) -fPIC -c SRC_FILES -o ../libbsdl.o
	$(CC) -g -shared  -Wl, -soname, libbsdl.so -o libbsdl.so libbsdl.o -lc

test:
	echo 'testing lib bsdl'
	cd test
	$(CC) -g -Wall SRC_FILES_TEST ../ -l ../src



