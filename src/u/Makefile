all:
	xxd -i release engine/include/gpeg/engine/release.h
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
	cd build && make clean
	cd engine && make clean
	cd compiler && make clean
	cd assembler && make clean
