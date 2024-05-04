all:
	cd src && make

debug:
	make all DEBUG="-D_DEBUG=1"

world: clean all specials doc test

specials:
	cd src/specials && make

.PHONY: test
test:
	cd test && make

.PHONY: doc
doc:
	cd doc && make

clean:
	@MFS=`find src/ doc/ -name Makefile | xargs grep -l '^clean:'`; \
		for MF in $$MFS; do \
			DIR=`dirname $$MF`; \
			make -C $$DIR clean; \
		done

superclean: clean
	@MFS=`find src/ doc/ -name Makefile | xargs grep -l '^superclean:'`; \
		for MF in $$MFS; do \
			DIR=`dirname $$MF`; \
			make -C $$DIR superclean; \
		done

archive: clean
	RELEASE=$$(cat release); \
	echo "  [TAR] gpeg-src-$$RELEASE.tar.gz"; \
	tar czf ~/work/archive/gpeg-src-$$RELEASE.tar.gz \
	  --transform "s,^,gpeg/,S" \
	  --exclude=\.git \
	  .

