#!/usr/local/bin/gnuplot
set terminal png enh size 1200,600 enhanced font "Times New Roman,24"
unset key
set pointsize 0.25
set xlabel "x"
set ylabel "y"
set view 50,20,1

set output 'solution_a.png'
splot 'solution_a.dat' using 1:2:3 title "Solution A" with points pt 3

set output 'solution_b.png'
splot 'solution_b.dat' using 1:2:3 title "Solution B" with points pt 3

set output 'solution_c.png'
splot 'solution_c.dat' using 1:2:3 title "Solution C" with points pt 3
