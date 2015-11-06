###############################################################################
#    Filename: Makefile
#
#      Author: David C. Drake (www.davidcdrake.com)
#
# Description: Makefile for the "Words of Power" text-based RPG. Written for a
#              Cygwin environment utilizing Digital Mars Make (5.05).
###############################################################################

CC = gcc
CFLAGS = -I.
HEADER = wop.h
OBJECTS = main.o characters.o combat.o dialogue.o items.o locations.o magic.o

.c.o:
	$(CC) -c -o $@ $< $(CFLAGS)

wop: $(OBJECTS) $(HEADER)
	$(CC) -o $@ $** $(CFLAGS)

.PHONY: clean

clean:
	-rm -f *.o *.stackdump
