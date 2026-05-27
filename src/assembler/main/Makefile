TARGET=gpega
CFLAGS=-g -O2 -Wall -Wextra -I../include $(DEBUG)
LIBS=../lib/libgpega.a ../../engine/lib/libgpege.a ../../util/src/lib/libutil.a
CC=$(ARCH)gcc

all: $(TARGET)

$(TARGET): gpega.o
	$(CC) -o $(TARGET) gpega.o $(LIBS)

clean:
		rm -f $(TARGET) gpega.o
