
DATA = language.data
CONV = g2
CONVFLAGS = -l amh
SOURCE = adari.sera \
         afar.sera \
         agew.sera \
         amharic.sera \
         bilin.sera \
         gedio.sera \
         geez.sera \
         oromo.sera \
         qotu.sera \
         sebatbeit.sera \
         sidamo.sera \
         siltie.sera \
         sodo.sera \
         tigre.sera \
         tigrigna.sera \
         universal.sera

OBJECTS = $(SOURCE:.sera=.data)

all: ${DATA}
 
${DATA}: $(OBJECTS)
		cat *.data > ${DATA}

local:

.sera.data:
		$(CONV) $(CONVFLAGS) $*.sera > $*.data

clean:
	    rm -f $(OBJECTS)

distclean:
	    rm -f $(OBJECTS)

