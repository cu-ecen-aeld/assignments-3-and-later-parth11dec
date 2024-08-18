CC      = gcc
CFLAGS  = -g -Wall
RM      = rm -f


default: all

all: writer

writer: writer.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o writer writer.c

clean veryclean:
	$(RM) *.o *.out writer

