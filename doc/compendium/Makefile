all:
	perl ./gen_doc_instructions.pl \
	  ../../src/gen0/res/instructions.pl \
	  ../../src/gen1/lib/assembler/assembly.gpeg
	perl ./generate.pl ../../src/gen0/res/instructions.pl .
	texi2pdf --batch compendium.tex >/dev/null || true

clean:
	rm -f compendium.aux compendium.lof compendium.log compendium.toc compendium.lot

superclean: clean
	rm -f compendium.pdf
