#!/bin/bash
# A script that launches gnuplot on the file result.dat

gnuplot -persist << EOF
	set title "Exact and approximate solution"
	set xlabel "Time"
	plot "result.dat" using 1:2 w lp lt 3 title "u", "result.dat" using 1:3 w l lw 2 lt 4 title "uex"
EOF
