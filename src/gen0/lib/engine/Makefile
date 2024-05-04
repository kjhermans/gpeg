OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpege.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
CURGEN?=../..
CFLAGS=-g -Wall -Wextra $(DEBUG) -I$(CURGEN)/include
ADDITIONALOBJECTS=\
  ../gpeg/gpeg_capturelist.o \
  ../gpeg/gpeg_opcode2string.o \

all: functionsheader $(LIB)

functionsheader: ../../include/gpeg/lib/engine/gpege_functions.h \
	gpege_functions.h

gpege_functions.h: *.c
	$(CURGEN)/bin/genfnchdr -t GPEG_ERR_T -i GPEGE_GEN0_PR_FUNCTIONS -g 0 . > \
	  gpege_functions.h

../../include/gpeg/lib/engine/gpege_functions.h: *.c
	$(CURGEN)/bin/genfnchdr -t GPEG_ERR_T -i GPEGE_GEN0_FUNCTIONS -G 0 . > \
	  ../../include/gpeg/lib/engine/gpege_functions.h

$(LIB): $(OBJECTS)
	$(AR) -rcs $(LIB) $(OBJECTS) $(ADDITIONALOBJECTS)

clean:
	rm -f $(OBJECTS) $(LIB)

superclean: clean
	rm -f gpege_functions.h \
	  ../../include/gpeg/lib/engine/gpege_functions.h
