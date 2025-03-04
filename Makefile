#---------------------------------------------------------------------------
# ANSI C compiler
#---------------------------------------------------------------------------
CC          = gcc
CFLAGS 		= -O -c -Wall -fno-strength-reduce #-g
LDFLAGS		= 

#---------------------------------------------------------------------------
# ELF specific (Linux)
#---------------------------------------------------------------------------
ELF_CC 		= gcc
ELF_CFLAGS	= -O2 -c -Wall
ELF_LINK    = gcc -shared -Wl,-t,-soname#

#---------------------------------------------------------------------------
# The Lexer
#---------------------------------------------------------------------------
LEX = flex            # use lex if flex not available

#---------------------------------------------------------------------------
# LibEth Depends
#
# SUPPORT_DOS  will return ^M with newlines
# SUPOORT_TEX  will compile with the TeX output map 
#              (excess memory if you do not use La/TeX)
# SUPPORT_IES  will compile with IES output maps
#              (requires SUPPORT_TEX)
# SUPPORT_ISO  will compile with ISO/TC46/SC2 output map 
# NO_LIBL      will compile with a built in yywrap so that the seralex.c
#              becomes portable when libeth will be used where libl is not present.
# USE_TALIGENT
#---------------------------------------------------------------------------

# DEPFLAGS = -DSUPPORT_DOS -DSUPPORT_TEX -DNO_LIBL -DSUPPORT_IES -DSUPPORT_ISO
DEPFLAGS = -DBUILDLIBETH -DSUPPORT_TEX -DNO_LIBL -DNO_LIBM -DSUPPORT_ISO -DSUPPORT_SERA -DUSE_TALIGENT

#---------------------------------------------------------------------------
# Directory where library is going to go when installed
#---------------------------------------------------------------------------
prefix = /usr
exec_prefix = ${prefix}
install_lib_dir = ${exec_prefix}/lib
install_include_dir = ${prefix}/include/libeth

#---------------------------------------------------------------------------
# Misc comamnds (safe to leave these untouched)
#---------------------------------------------------------------------------
RANLIB 		= ranlib
INSTALL		= /usr/bin/install -c       # hopefully this is "ginstall"
INSTALL_DATA	= ${INSTALL} -m 644
INSTALL_DIR	= ${INSTALL} -d -m 755
RM 		= rm -f
RM_R		= rm -rf
AR_CR 		= ar cr
RMDIR 		= rmdir
LN 		= ln -sf
CP 		= cp
MKDIR		= mkdir

#---------------------------------------------------------------------------
# There should be no need to change anything below here.
#---------------------------------------------------------------------------
THIS_LIB = eth

NORMAL_LIB = lib$(THIS_LIB).a

ELF_MAJOR_VERSION   = 0#
ELF_MINOR_VERSION   = 3.4#
ELFLIB = lib$(THIS_LIB).so#
ELFLIB_MAJOR = $(ELFLIB).$(ELF_MAJOR_VERSION)#
ELFLIB_MAJOR_MINOR = $(ELFLIB).$(ELF_MAJOR_VERSION).$(ELF_MINOR_VERSION)#

INCLUDEDIR = ./include
TALINCLUDEDIR = ./taligent#

ETHSRC = lib-src/etctype.c lib-src/etmath.c lib-src/etstdio.c lib-src/etstdlib.c lib-src/etstring.c lib-src/ettime.c lib-src/lethutil.c lib-src/redterms.c lib-src/sysinfo.c lib-src/langxs.c
ETHOBJS = $(ETHSRC:.c=.o)
SYSTEMS = systems/seralex.c systems/taligent/cvtutf.c systems/taligent/cvtutf7.c systems/base.c systems/absha.c systems/acis.c systems/acuwork.c systems/addisword.c systems/alpas.c systems/brana.c systems/cbhale.c systems/dehai.c systems/dejene.c systems/ed.c systems/enhpfr.c systems/ethiop.c systems/ethiopic.c systems/ethiome.c systems/ethiosys.c systems/ethiowalia.c systems/feedel.c systems/filters.c systems/fidelxtr.c systems/geezfont.c systems/geezfree.c systems/ies.c systems/iso.c systems/java.c systems/jis.c systems/junet.c systems/mainz.c systems/monotype.c systems/nci.c systems/ncic.c systems/omnitech.c systems/phonetic.c systems/powergez.c systems/qubee.c systems/samawerfa.c systems/sera.c systems/tfanus.c systems/unicode.c systems/visgeez.c systems/wazema.c systems/systemio.c
SYSOBJS = $(SYSTEMS:.c=.o)
DOCTYPES = doctypes/html.c doctypes/rtf.c doctypes/tex.c 
DOCOBJS = $(DOCTYPES:.c=.o)
CALENDAR = calendar/etime.c calendar/Ethiopic.c calendar/Gregorian.c
CALOBJS = $(CALENDAR:.c=.o)
MEMBERS = $(ETHOBJS) $(SYSOBJS) $(CALOBJS) $(DOCOBJS)
ARFLAGS = rcv
 
SHELL = /bin/sh
#---------------------------------------------------------------------------
# Rules
#---------------------------------------------------------------------------
all: $(MEMBERS)
	-$(RM) $(NORMAL_LIB)
	$(AR) $(ARFLAGS) $(NORMAL_LIB) $(MEMBERS) 
	$(RANLIB) $(NORMAL_LIB)
	@echo ""
	@echo $(NORMAL_LIB) created in `pwd`.

elf: $(MEMBERS)
	$(ELF_LINK),$(ELFLIB_MAJOR) -o $(ELFLIB_MAJOR_MINOR) $(MEMBERS)
	$(LN) $(ELFLIB_MAJOR) $(ELFLIB)
	@echo ""
	@echo $(ELFLIB_MAJOR_MINOR) created in `pwd`. 
	@echo The link $(ELFLIB_MAJOR) to $(ELFLIB_MAJOR_MINOR) was also created.
	@echo ""

$(ETHOBJS): $(ETHSRC)
	cd lib-src; make;

$(SYSOBJS): $(SYSTEMS)
	cd systems; make;

$(DOCOBJS): $(DOCTYPES)
	cd doctypes; make;

$(CALOBJS): $(CALENDAR)
	cd calendar; make libobjs;

#---------------------------------------------------------------------------
# Housekeeping
#---------------------------------------------------------------------------
clean:
	cd calendar; make clean;
	cd doctypes; make clean;
	cd lib-src; make clean;
	cd systems; make clean;
	    
distclean:
	cd calendar; make distclean;
	cd doctypes; make distclean;
	cd lib-src; make distclean;
	cd systems; make distclean;
	    

#---------------------------------------------------------------------------
# Intallation rules
#---------------------------------------------------------------------------
install: $(OBJDIR_NORMAL_LIB) $(install_include_dir)
	@echo installing $(NORMAL_LIB) in $(install_lib_dir)
	$(INSTALL_DATA) $(NORMAL_LIB) $(install_lib_dir)
	$(RANLIB) $(install_lib_dir)/$(NORMAL_LIB)
	chmod 644 $(install_lib_dir)/$(NORMAL_LIB)
	@echo installing headers into $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/fidel.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/libeth.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/etstdlib.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/etstdio.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/etstring.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/etctype.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/ettime.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/etmath.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/sysinfo.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/langxs.h $(install_include_dir)
	$(INSTALL_DATA) doctypes/html.h $(install_include_dir)
	$(INSTALL_DATA) doctypes/rtf.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/greek.h $(install_include_dir)
	$(INSTALL_DATA) calendar/etime.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/config.h $(install_include_dir)
	$(INSTALL_DATA) systems/exports.h $(install_include_dir)
	$(INSTALL_DATA) systems/filters.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/maptypes.h $(install_include_dir)
	$(INSTALL_DATA) $(INCLUDEDIR)/RedTags.sera $(install_include_dir)
$(install_include_dir):
	$(INSTALL_DIR) -d  $(install_include_dir)
install-elf: all install elf $(install_lib_dir) $(install_include_dir) $(ELFDIR_ELF_LIB)
	-$(RM) $(install_lib_dir)/$(ELFLIB)
	-$(RM) $(install_lib_dir)/$(ELFLIB_MAJOR)
	@echo installing $(ELFLIB_MAJOR_MINOR) in $(install_lib_dir)
	$(INSTALL_DATA) $(ELFLIB_MAJOR_MINOR) $(install_lib_dir)
	@echo creating symbolic links to $(ELFLIB_MAJOR_MINOR)
	-cd $(install_lib_dir); $(LN) $(ELFLIB_MAJOR_MINOR) $(ELFLIB_MAJOR)
	@echo ""
	@echo $(ELFLIB_MAJOR_MINOR) created in $(install_lib_dir).
	@echo The link $(ELFLIB_MAJOR) to $(ELFLIB_MAJOR_MINOR) was also created.
