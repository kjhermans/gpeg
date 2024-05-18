PREVGEN?=../../../gen0
CURGEN?=../..
CFILES:=$(shell ls *.c | sort)
OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpegc.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
INCLUDE=-I$(CURGEN)/include
CFLAGS=-g -Wall -Wextra $(DEBUG) -DPREVGEN=gen0_ $(INCLUDE)

all: grammarh functionsh lib

lib: objects
	$(AR) -rcs $(LIB) $(OBJECTS)

objects: $(OBJECTS)

grammarh: grammar.h

grammar.h: grammar.byc
	xxd -c 8 -p grammar.byc | sed 's/\(..\)/0x\1, /g' > grammar.h

grammar.byc:grammar.asm
	$(PREVGEN)/bin/gpega -i grammar.asm -o grammar.byc

grammar.asm: grammar.gpeg
	$(PREVGEN)/bin/gpegc -C -i grammar.gpeg -o grammar.asm \
	  -G grammar.c gpegc -M grammar.slotmap.h
	grep 'include\|extern' grammar.c > grammar_functions.h

functionsh: gpegc_functions.h

gpegc_functions.h: $(CFILES)
	../../bin/genfnchdr -t GPEG_ERR_T -i GPEGC_PRIVATE_FUNCTIONS_H_ . > \
	  gpegc_functions.h

#$(INCLUDE)/gpeg/lib/compiler/gpegc_functions.h: $(CFILES)
#	../../bin/genfnchdr -t GPEG_ERR_T -i GPEGC_FUNCTIONS_H_ . > \
#	  $(INCLUDE)/gpeg/lib/compiler/gpegc_functions.h

clean:
	rm -f grammar.asm grammar.byc $(OBJECTS) $(LIB)

superclean: clean
	rm -f grammar.h \
	  gpegc_functions.h
