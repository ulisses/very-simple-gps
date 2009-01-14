all:
	dot -Tps grafo.dot -o grafo.ps
	#dot -Tps memoria.dot -o memoria.ps -s
	#dot -Tps grafo_memoria.dot -o grafo_memoria.ps -s
	#ps2pdf file.ps > file.pdf
	#ps2pdf memoria.ps > memoria.pdf
	ps2pdf grafo.ps > grafo.pdf
	#gs -q -dNOPAUSE -dBATCH -dTextAlphaBits=4 -dGraphicsAlphaBits=4 -sDEVICE=png16m -sOutputFile=file.png file.ps
	#acroread file.pdf
	xpdf grafo.pdf
