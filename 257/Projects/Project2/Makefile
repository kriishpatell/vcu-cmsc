CC = gcc
FLAGS = -g -c -Wall
OUT	= cmsc257-s22-p2

OBJS = cmsc257-s22-p2.o p2-support.o
SOURCE = cmsc257-s22-p2.c p2-support.c
DEPS = p2-support.h

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

cmsc257-s22-p2.o: cmsc257-s22-p2.c
	$(CC) $(FLAGS) cmsc257-s22-p2.c 

p2-support.o: p2-support.c
	$(CC) $(FLAGS) p2-support.c 

clean:
	rm -v cmsc257-s22-p2 $(OBJS)


