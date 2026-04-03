all:
	./gpegc -i xml.gpeg -o xml.asm
	./gpega -i xml.asm -o xml.byc
	./gpege -i xml.txt -c xml.byc

clean:
	rm -f *.asm *.byc
