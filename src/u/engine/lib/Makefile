OBJECTS:=$(shell ls *.c | sort | sed -e 's/\.c$$/.o/')
LIB=libgpegue.a
CC=$(ARCH)gcc
AR=$(ARCH)ar
CFLAGS=-g -O2 -Wall -Wextra -I../include

all: $(LIB)

$(LIB): $(OBJECTS)
	$(AR) -rcs $(LIB) $(OBJECTS)
