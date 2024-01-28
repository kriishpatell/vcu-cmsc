OBJS	= main.o mem-mgmt.o
SOURCE	= main.c mem-mgmt.c
HEADER	= mem-mgmt.h
OUT	= exec
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

mem-mgmt.o: mem-mgmt.c
	$(CC) $(FLAGS) mem-mgmt.c 

clean:
	rm -f $(OBJS) $(OUT)