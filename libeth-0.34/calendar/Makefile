
CC = gcc
CFLAGS = -c -Wall #-g
PROG =  edate
PROGSRC = bin/edate.c
LIBM = -lm
STRIP = strip
SOURCE  = Ethiopic.c Gregorian.c etime.c
OBJECTS = $(SOURCE:.c=.o)

 
libobjs: $(OBJECTS)
	$(CC) -DBUILDLIBETH $(CFLAGS) $(SOURCE)

libobjs-nolibm: $(OBJECTS)
	$(CC) -DUSELIBETH -DNO_LIBM $(CFLAGS) $(SOURCE)

nolibm:  $(OBJECTS)
	    $(CC) -g -DNO_LIBM $(SOURCE) 

all: ${PROG}
 
${PROG}: $(OBJECTS)
	    $(CC) -Wall $(OBJECTS) $(PROGSRC) $(LIBM) -o ${PROG}
		$(STRIP) $(PROG)

local:

.c.o:
		$(CC) $(CFLAGS) $*.c

clean:
	    rm -f $(OBJECTS)

distclean:
	    rm -f $(OBJECTS)

