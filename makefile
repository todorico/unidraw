all:
	clear
	mkdir -p "bin"
	make -f make_main
	make -f make_par
	make -f make_vois
	make -f make_col
 