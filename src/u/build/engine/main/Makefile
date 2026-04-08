TARGET=gpege
CFLAGS=-g -O2 -Wall -Wextra -I../include $(DEBUG)

all: $(TARGET)

$(TARGET): gpege.o
	$(CC) -o $(TARGET) gpege.o ../lib/libgpege.a -landy

clean:
		rm -f $(TARGET) gpege.o
