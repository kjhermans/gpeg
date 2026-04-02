all: test_coverage

test_coverage:
	./gpegc -i coverage.gpeg -o coverage.asm
	./gpega -i coverage.asm -o coverage.byc
	./gpege -i coverage.txt -c coverage.byc
