PREVGEN?=../../../gen0
CURGEN?=../../../gen1
OBJECTS=gpegd.o
CC=$(ARCH)gcc
AR=$(ARCH)ar
CFLAGS=-g -Wall -Wextra $(DEBUG) -I$(CURGEN)/include
TARGET=gpegd
LIBS=\
  ../../lib/assembler/libgpegd.a \
  ../../lib/gpeg/libgpeg.a \
  ../../lib/util/libutil.a \
  $(PREVGEN)/lib/engine/libgpege.a \

all: $(TARGET)

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	rm -f $(OBJECTS) $(TARGET)
