OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpege_dbgncrs.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
CURGEN?=../../..
CFLAGS=-g -Wall -Wextra $(DEBUG) -I$(CURGEN)/include

all: functionsheader $(LIB)

functionsheader: gpege_dbgncrs_functions.h

gpege_dbgncrs_functions.h: *.c
	$(CURGEN)/bin/genfnchdr -t GPEG_ERR_T \
	  -i GPEGE_GEN0_PR_DBGNCRS_FUNCTIONS -g 0 . > \
	  gpege_dbgncrs_functions.h

../../include/gpeg/lib/engine/gpege_functions.h: *.c
	$(CURGEN)/bin/genfnchdr -t GPEG_ERR_T -i GPEGE_GEN0_FUNCTIONS -G 0 . > \
	  ../../include/gpeg/lib/engine/gpege_functions.h

$(LIB): $(OBJECTS)
	$(AR) -rcs $(LIB) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(LIB)

superclean: clean
	rm -f gpege_functions.h \
	  ../../include/gpeg/lib/engine/gpege_functions.h
