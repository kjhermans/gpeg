all:
	cd build && make
	cd engine && make
	cd compiler && make
	cd assembler && make

.PHONY: test

test:
	cd test && make

debug:
	make all DEBUG="-D_DEBUG=1"

clean:
	cd engine && make clean
