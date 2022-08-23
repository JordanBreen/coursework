#!/usr/local/bin/gnuplot
data_dest = system("echo $DATA_DEST")
imag_dest = system("echo $IMAG_DEST")
plot_name = system("echo $PLOT_NAME")
set terminal png enh size 1200,600 enhanced font "Times New Roman,24"
unset key
set pointsize 0.25
set xlabel "x"
set ylabel "y"
set view 50,20,1
set output imag_dest
splot data_dest using 1:2:3 title plot_name with points pt 3
