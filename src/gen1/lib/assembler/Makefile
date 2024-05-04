PREVGEN?=../../../gen0
CURGEN?=../..
CFILES:=$(shell ls *.c | sort)
OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpega.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
INCLUDE=-I$(CURGEN)/include
CFLAGS=-g -Wall -Wextra $(DEBUG) -DPREVGEN=gen0_ $(INCLUDE)

all: assemblyh instructionsh functionsh lib

lib: objects
	$(AR) -rcs $(LIB) $(OBJECTS)

objects: $(OBJECTS)

assemblyh: assembly.h

assembly.h: assembly.byc
	xxd -c 8 -p assembly.byc | sed 's/\(..\)/0x\1, /g' > assembly.h

assembly.byc:assembly.asm
	$(PREVGEN)/bin/gpega -i assembly.asm -o assembly.byc

assembly.asm: assembly.gpeg
	$(PREVGEN)/bin/gpegc -C -i assembly.gpeg -o assembly.asm -G assembly.c \
	  -M assembly.slotmap.h
	grep 'include\|extern' assembly.c > assembly_functions.h

instructionsh: gpega_instructions.h
	../../bin/geninstrhdr $(CURGEN)/res/instructions.pl > gpega_instructions.h

gpega_instructions.h: $(CURGEN)/res/instructions.pl

functionsh: gpega_functions.h

gpega_functions.h: $(CFILES)
	../../bin/genfnchdr -t GPEG_ERR_T -i GPEGC_PRIVATE_FUNCTIONS_H_ . > \
	  gpega_functions.h

clean:
	rm -f assembly.asm assembly.byc $(OBJECTS) $(LIB)

superclean: clean
	rm -f assembly.h \
	  gpega_functions.h \
	  gpega_instructions.h \

