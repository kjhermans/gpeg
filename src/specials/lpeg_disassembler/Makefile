all: lpegd

lpegd: main.c
	$(CC) -g -O2 -Wall -Wextra -o lpegd \
	  -I../../gen2/include/ main.c ../../gen2/lib/util/libutil.a

clean:
	rm -f lpegd
