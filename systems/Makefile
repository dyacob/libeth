
CC = gcc
CFLAGS = -c -Wall #-g
DEPFLAGS = -DBUILDLIBETH
INCLUDEDIR = ../include
LEX = flex            # use lex if flex not available
SOURCE  = base.c \
          absha.c \
          acis.c \
          acuwork.c \
          addisword.c \
          alpas.c \
          braille.c \
          brana.c \
          cbhale.c \
          cvtutf.c \
          cvtutf7.c \
          dehai.c \
          dejene.c \
          ed.c \
          enhpfr.c \
          ethiome.c \
          ethiop.c \
          ethiopic.c \
          ethiosys.c \
          ethiowalia.c \
          feedel.c \
          fidelxtr.c \
          filters.c \
          geezfont.c \
          geezfree.c \
          ies.c \
          iso.c \
          java.c \
          jis.c \
          junet.c \
          mainz.c \
          monotype.c \
          nci.c \
          ncic.c \
          omnitech.c \
          phonetic.c \
          powergez.c \
          qubee.c \
          samawerfa.c \
          sera.c \
          seralex.c \
          tfanus.c \
          unicode.c \
          visgeez.c \
          wazema.c \
          systemio.c
OBJECTS = $(SOURCE:.c=.o)

 
all: $(OBJECTS)

seralex.c:  seralex.l
	${LEX} -t seralex.l > seralex.c

cvtutf.o:
	$(CC) $(CFLAGS) $(DEPFLAGS) -Italigent taligent/cvtutf.c
	cd taligent; ln -sf ../cvtutf.o .;

cvtutf7.o:
	$(CC) $(CFLAGS) $(DEPFLAGS) -Italigent taligent/cvtutf7.c
	cd taligent; ln -sf ../cvtutf7.o .;


local:

.c.o:
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INCLUDEDIR) $*.c

clean:
	    rm -f $(OBJECTS)

distclean:
	    rm -f $(OBJECTS) seralex.c taligent/*.o
