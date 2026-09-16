all: 0001

0001:
	./gpegc -C -i unit_0001.gpeg -o /tmp/unit_0001.asm
	./gpega -i /tmp/unit_0001.asm -o /tmp/unit_0001.byc
	xxd -i /tmp/unit_0001.byc ./unit_0001_bytecode.h
	$(CC) -g -O2 -Wall -Wextra \
		-o /tmp/unit_0001.exe \
		unit_0001.c \
		./libgpege.a ./libandy.a
	/tmp/unit_0001.exe
