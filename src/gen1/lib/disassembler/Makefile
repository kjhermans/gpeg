PREVGEN?=../../../gen0
CURGEN?=../..
CFILES:=$(shell ls *.c | sort) disasm.c
OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpegd.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
INCLUDE=$(CURGEN)/include
CFLAGS=-g -Wall -Wextra $(DEBUG) -DPREVGEN=gen0_ -I$(INCLUDE)

all: disasmh functionsh lib

disasmh: disasm.h

disasm.h: disasm.byc
	xxd -c 8 -p disasm.byc | sed 's/\(..\)/0x\1, /g' > disasm.h

disasm.byc: disasm.asm
	$(PREVGEN)/bin/gpega -i disasm.asm -o disasm.byc

disasm.asm: disasm.gpeg
	$(PREVGEN)/bin/gpegc -i disasm.gpeg -o disasm.asm -G disasm.c \
	  -M disasm.slotmap.h

disasm.gpeg: ../../res/instructions.pl
	../../bin/gendisasm.pl ../../res/instructions.pl > disasm.gpeg

functionsh: gpegd_functions.h

gpegd_functions.h: $(CFILES)
	../../bin/genfnchdr -t GPEG_ERR_T -i GPEGD_PRIVATE_FUNCTIONS_H_ . > \
	  gpegd_functions.h


lib: objects
	$(AR) -rcs $(LIB) $(OBJECTS)

objects: $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(LIB)

superclean: clean
	rm -f disasm.gpeg disasm.asm disasm.byc disasm.slotmap.h \
	  disasm.h
