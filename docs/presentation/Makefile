all:
	pdflatex presentation.tex
	pdflatex presentation.tex
	pdflatex presentation.tex
	# 3 times for correct toc generation!
	
clean:
	# remove latex compile help files
	rm -rf *.aux *.log *.toc *.nav *.out *.snm

web:
	make all
	cp -fv presentation.pdf ~/public_html
	chmod o+r ~/public_html/presentation.pdf
