OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpeg.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
CURGEN?=../..
CFLAGS=-g -Wall -Wextra $(DEBUG) -I$(CURGEN)/include

all: maph instructionsh functionsh $(LIB)

maph: map.h

map.h: map.byc
	xxd -c 8 -p map.byc | sed 's/\(..\)/0x\1, /g' > map.h

map.byc: map.asm $(CURGEN)/bin/gpega
	$(CURGEN)/bin/gpega -i map.asm -o map.byc

map.asm: map.gpeg $(CURGEN)/bin/gpegc
	$(CURGEN)/bin/gpegc -i map.gpeg -o map.asm

instructionsh: ../../include/gpeg/lib/gpeg/gpeg_instructions.h

../../include/gpeg/lib/gpeg/gpeg_instructions.h: ../../res/instructions.pl
	$(CURGEN)/bin/geninstrhdr ../../res/instructions.pl > \
	  ../../include/gpeg/lib/gpeg/gpeg_instructions.h

functionsh: ../../include/gpeg/lib/gpeg/gpeg_functions.h gpeg_functions.h

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
	  ../../include/gpeg/lib/gpeg/gpeg_functions.h \
	  map.h map.byc map.asm
