TARGET=gpege
CFLAGS=-g -O2 -Wall -Wextra -I../include $(DEBUG)
CC=$(ARCH)gcc
LIBS=../lib/libgpege.a ../../util/src/lib/libutil.a

all: $(TARGET)

$(TARGET): gpege.o
	$(CC) -o $(TARGET) gpege.o $(LIBS)

clean:
		rm -f $(TARGET) gpege.o
