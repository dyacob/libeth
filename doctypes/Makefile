
CC = gcc
CFLAGS = -c -Wall #-g
DEPFLAGS = -DBUILDLIBETH
INCLUDEDIR = ../include
SOURCE  = html.c rtf.c tex.c
OBJECTS = $(SOURCE:.c=.o)

 
all: $(OBJECTS)

local:

.c.o:
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INCLUDEDIR) $*.c

clean:
	    rm -f $(OBJECTS)

distclean:
	    rm -f $(OBJECTS)


