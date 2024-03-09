OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpeg.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
CURGEN?=../..
CFLAGS=-g -Wall -Wextra $(DEBUG) -I$(CURGEN)/include

all: instructionsheader functionsheader $(LIB)

instructionsheader: ../../include/gpeg/lib/gpeg/gpeg_instructions.h

../../include/gpeg/lib/gpeg/gpeg_instructions.h: ../../res/instructions.pl
	$(CURGEN)/bin/geninstrhdr ../../res/instructions.pl > \
	  ../../include/gpeg/lib/gpeg/gpeg_instructions.h

functionsheader: ../../include/gpeg/lib/gpeg/gpeg_functions.h gpeg_functions.h

../../include/gpeg/lib/gpeg/gpeg_functions.h: *.c
	$(CURGEN)/bin/genfnchdr -t GPEG_ERR_T -i GPEG_FUNCTIONS . > \
	  ../../include/gpeg/lib/gpeg/gpeg_functions.h

gpeg_functions.h: *.c
	$(CURGEN)/bin/genfnchdr -t GPEG_ERR_T -i GPEG_PR_FUNCTIONS -g 0 . > \
	  gpeg_functions.h

$(LIB): $(OBJECTS)
	$(AR) -rcs $(LIB) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(LIB)

superclean: clean
	rm -f gpeg_functions.h \
	  ../../include/gpeg/lib/gpeg/gpeg_instructions.h \
	  ../../include/gpeg/lib/gpeg/gpeg_functions.h
