
CC = gcc
CFLAGS = -c -Wall #-g
DEPFLAGS = -DBUILDLIBETH -DUSE_TALIGENT
INCLUDEDIR = ../include
SOURCE  = etctype.c etmath.c etstdio.c etstdlib.c etstring.c ettime.c lethutil.c redterms.c sysinfo.c langxs.c
OBJECTS = $(SOURCE:.c=.o)

 
all: $(OBJECTS)

local:

.c.o:
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INCLUDEDIR) $*.c

clean:
	    rm -f $(OBJECTS)

distclean:
	    rm -f $(OBJECTS)
