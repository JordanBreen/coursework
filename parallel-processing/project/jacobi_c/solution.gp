#set terminal png enh size 1200,600 enhanced font "Times New Roman,24"
#set output 'solution.png'

set nokey
set pointsize 0.25
set xlabel "x"
set ylabel "y"
set view 50,20,1
splot \
 'solution.dat' using 1:2:3 title "" with points pt 3