OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/') simap.o
LIB=libgpege.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
CURGEN?=../..
CFLAGS=-g -Wall -Wextra $(DEBUG) -I$(CURGEN)/include
ADDITIONALOBJECTS=\
  ../gpeg/gpeg_capturelist.o \
  ../gpeg/gpeg_opcode2string.o \

all: maplogic functionsheader $(LIB) subdirs

subdirs:
	cd gpege_debug_ncurses/ && make

maplogic: simap.h caplist.h

simap.c: simap.asm

simap.h: simap.byc
	xxd -c 8 -p simap.byc | sed 's/\(..\)/0x\1, /g' > simap.h

simap.byc: simap.asm
	$(CURGEN)/bin/gpega -i simap.asm -o simap.byc

simap.asm: simap.gpeg
	$(CURGEN)/bin/gpegc -C -i simap.gpeg -o simap.asm \
	  -G simap.c simap -M simap.slotmap.h

caplist.c: caplist.asm

caplist.h: caplist.byc
	xxd -c 8 -p caplist.byc | sed 's/\(..\)/0x\1, /g' > caplist.h

caplist.byc: caplist.asm
	$(CURGEN)/bin/gpega -i caplist.asm -o caplist.byc

caplist.asm: caplist.gpeg
	$(CURGEN)/bin/gpegc -C -i caplist.gpeg -o caplist.asm \
	  -G caplist.c caplist -M caplist.slotmap.h

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
	rm -f simap.h simap.byc simap.asm simap.slotmap.h simap.c
	rm -f caplist.h caplist.byc caplist.asm caplist.slotmap.h caplist.c
