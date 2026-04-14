TARGET=gpega
CFLAGS=-g -O2 -Wall -Wextra -I../include $(DEBUG)
LIBS=../lib/libgpega.a ../../engine/lib/libgpege.a

all: $(TARGET)

$(TARGET): gpega.o
	$(CC) -o $(TARGET) gpega.o $(LIBS) -landy

clean:
		rm -f $(TARGET) gpega.o
