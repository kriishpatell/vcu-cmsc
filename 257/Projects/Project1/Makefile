# Makefile for the CMSC257 Project1 #

# Make environment
CC=gcc
CFLAGS= -c -g -Wall $(INCLUDES)


# Files
OBJECT_FILES=	p1.o p1-support.o

# Productions
all : cmsc257-s22-p1

cmsc257-s22-p1 : $(OBJECT_FILES)
	$(CC)  $(OBJECT_FILES) -o $@ 

p1.o : cmsc257-s22-p1.c p1-support.h
	$(CC) $(CFLAGS) $< -o $@

p1-support.o : p1-support.c p1-support.h 
	$(CC) $(CFLAGS) $< -o $@

clean : 
	rm -v cmsc257-s22-p1 $(OBJECT_FILES)
