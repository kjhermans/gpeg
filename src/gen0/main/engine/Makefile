CURGEN?=../../
OBJECTS=gpege.o
CC=$(ARCH)gcc
AR=$(ARCH)ar
CFLAGS=-g -Wall -Wextra $(DEBUG) -I$(CURGEN)/include
TARGET=gpege
LIBS=\
  $(CURGEN)/lib/engine/libgpege.a \
  ../../lib/gpeg/libgpeg.a \
  ../../lib/util/libutil.a \

all: $(TARGET)

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	rm -f $(OBJECTS) $(TARGET)
