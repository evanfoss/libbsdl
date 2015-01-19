# libbsdl
# root Makefile
# By Evan Foss
# Date 2015.01.19

CC := gcc
SRC_FILES = \
	libbsdl.c \
	libbsdl.h

SRC_FILES_TEST = 
	main.c \

all: libbsdl test


libbsdl:
	echo 'building libbsdl'
	cd src
	$(CC) -c SRC_FILES -o ../libbsdl.o
	ar rcs libbsdl.a libbsdl.o

test:
	cd test
	echo 'testing libbsdl'
	$(CC) -I SRC_FILES_TEST ../libbsdl.so ../
