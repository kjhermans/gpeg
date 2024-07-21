include composition.make

all:
	./echo_setup.sh
	cd gen0 && make GPEG_COMPOSITION=$(GPEG_COMPOSITION)
	cd gen1 && make GPEG_COMPOSITION=$(GPEG_COMPOSITION)
	cd gen2 && make GPEG_COMPOSITION=$(GPEG_COMPOSITION)

instructions:
	cd gen0 && make instructions
	cd gen1 && make instructions
	cd gen2 && make instructions
