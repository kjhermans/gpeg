CFLAGS=-g -O2 -Wall -Wextra -I../../gen1/include
LIBS=\
  ../../gen2/lib/gpeg/libgpeg.a \
  ../../gen2/lib/util/libutil.a \
  ../../gen2/lib/engine/libgpege.a

all: assembly_handler.o lpega

lpega:
	$(CC) -o lpega *.o $(LIBS)

clean:
	rm -f assembly_handler.o lpega
