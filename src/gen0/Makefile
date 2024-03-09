CURDIR=$(shell pwd)
GPEGC=$(CURDIR)/bin/gpegc

all:
	cd lib && make
	cd main && make

testing:
	DIRS=`find test/compiler -maxdepth 1 -type d | grep test | sort -n`; \
	for DIR in $$DIRS; do \
	  echo "GOING TO DIR $$DIR"; \
	  cd $$DIR && make GPEGC=$(GPEGC); \
	  cd $(CURDIR); \
	done
