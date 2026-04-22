all:
	perl ./gendoc.pl
	texi2pdf --batch compendium.tex >/dev/null || true

clean:
	rm -f compendium.aux compendium.lof compendium.log compendium.toc compendium.lot

superclean: clean
	rm -f compendium.pdf
