all:
	pdflatex mvc.tex
	bibtex mvc
	pdflatex mvc.tex
	pdflatex mvc.tex
	# 3 times for correct toc generation!
	
clean:
	# remove latex compile help files
	rm -rf *.aux *.idx *.log *.toc *.bbl *.blg

web:
	make all
	cp -fv mvc.pdf ~/public_html
	chmod o+r ~/public_html/mvc.pdf

