PREVGEN?=../../../gen0
CURGEN?=../..
CFILES:=$(shell ls *.c | sort)
OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpegt.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
INCLUDE=-I$(CURGEN)/include
CFLAGS=-g -Wall -Wextra $(DEBUG) -DPREVGEN=gen0_ $(INCLUDE)

all: transformh functionsh lib

lib: objects
	$(AR) -rcs $(LIB) $(OBJECTS)

objects: $(OBJECTS)

transformh: transform.h

transform.h: transform.byc
	xxd -c 8 -p transform.byc | sed 's/\(..\)/0x\1, /g' > transform.h

transform.byc:transform.asm
	$(PREVGEN)/bin/gpega -i transform.asm -o transform.byc

transform.asm: transform.gpeg
	$(PREVGEN)/bin/gpegc -C -i transform.gpeg -o transform.asm \
	  -G transform.c gpegt -M transform.slotmap.h
	grep 'include\|extern' transform.c > transform_functions.h

functionsh: gpegt_functions.h

gpegt_functions.h: $(CFILES)
	../../bin/genfnchdr -t GPEG_ERR_T -i GPEGC_PRIVATE_FUNCTIONS_H_ . > \
	  gpegt_functions.h

clean:
	rm -f transform.asm transform.byc $(OBJECTS) $(LIB)

superclean: clean
	rm -f transform.h \
	  gpegt_functions.h
