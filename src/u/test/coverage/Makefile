all:
	./gpegc -i coverage.gpeg -o coverage.asm
	./gpega -i coverage.asm -o coverage.byc
	./gpege -i coverage.txt -c coverage.byc

clean:
	rm -f *.asm *.byc
