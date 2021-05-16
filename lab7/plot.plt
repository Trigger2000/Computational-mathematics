set terminal svg enhanced size 1000 1000

set output "plot_0.5.svg"
set xlabel "x"
set ylabel "y"
plot "./data1.dat" using 1:2 with lines

set output "plot_1.0.svg"
set xlabel "x"
set ylabel "y"
plot "./data2.dat" using 1:2 with lines

set output "plot_1.4.svg"
set xlabel "x"
set ylabel "y"
plot "./data3.dat" using 1:2 with lines