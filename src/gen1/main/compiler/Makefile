PREVGEN?=../../../gen0
CURGEN?=../../../gen1
OBJECTS=gpegc.o
CC=$(ARCH)gcc
AR=$(ARCH)ar
CFLAGS=-g -Wall -Wextra $(DEBUG) -I$(CURGEN)/include
TARGET=gpegc
LIBS=\
  ../../lib/compiler/libgpegc.a \
  ../../lib/gpeg/libgpeg.a \
  ../../lib/util/libutil.a \
  $(PREVGEN)/lib/engine/libgpege.a \

all: $(TARGET)

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

#	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS) -static -static-libgcc
#	if [ "x$(DEBUG)" = "x" ]; then strip $(TARGET); fi

clean:
	rm -f $(OBJECTS) $(TARGET)
