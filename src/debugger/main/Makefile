TARGET=gpege_dbg
CFLAGS=-g -O2 -Wall -Wextra -I../include -D_DEBUG

all: $(TARGET)

$(TARGET): gpege.o
	$(CC) -o $(TARGET) gpege.o ../lib/libgpege.a -landy

clean:
		rm -f $(TARGET) gpege.o
