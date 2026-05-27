TARGET=gpegc
CFLAGS=-g -O2 -Wall -Wextra -I../include $(DEBUG)
LIBS=../lib/libgpegc.a ../../engine/lib/libgpege.a ../../util/src/lib/libutil.a
CC=$(ARCH)gcc

all: $(TARGET)

$(TARGET): gpegc.o
	$(CC) -o $(TARGET) gpegc.o $(LIBS)

clean:
		rm -f $(TARGET) gpegc.o
