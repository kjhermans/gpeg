TARGET=gpegc
CFLAGS=-g -O2 -Wall -Wextra -I../include $(DEBUG)
LIBS=../lib/libgpegc.a ../../engine/lib/libgpege.a

all: $(TARGET)

$(TARGET): gpegc.o
	$(CC) -o $(TARGET) gpegc.o $(LIBS) -landy

clean:
		rm -f $(TARGET) gpegc.o
