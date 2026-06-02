OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpege.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
CFLAGS=-g -O2 -Wall -Wextra -Wshadow -D_DEBUG -D_DEBUGGER -fPIC -I../include

all: labelmap $(LIB)

labelmap: labelmap_bytecode.h labelmap_slotmap.h

labelmap_bytecode.h: labelmap.byc
	xxd -i labelmap.byc labelmap_bytecode.h

labelmap.byc: labelmap.asm
	gpega -i labelmap.asm -o labelmap.byc

labelmap_slotmap.h: labelmap.gpeg
	gpegc -i labelmap.gpeg -o labelmap.asm -M labelmap_slotmap.h

labelmap.asm: labelmap.gpeg
	gpegc -i labelmap.gpeg -o labelmap.asm -M labelmap_slotmap.h

$(LIB): $(OBJECTS)
	$(AR) -rcs $(LIB) $(OBJECTS)

clean:
	rm -f $(LIB) $(OBJECTS)
