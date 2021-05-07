set terminal svg enhanced size 1000 1000

set output "plot_xyt_simple.svg"
set xlabel "t"
set ylabel "x, y"
plot "./data1.dat" using 5:1 with lines title "x", "./data1.dat" using 5:2 with lines title "y"

set output "plot_a1a2t_simple.svg"
set xlabel "t"
set ylabel "a1, a2"
plot "./data1.dat" using 5:3 with lines title "a1", "./data1.dat" using 5:4 with lines title "a2"

set output "plot_xyt_modified.svg"
set xlabel "t"
set ylabel "x, y"
plot "./data2.dat" using 5:1 with lines title "x", "./data2.dat" using 5:2 with lines title "y"

set output "plot_a1a2t_modified.svg"
set xlabel "t"
set ylabel "a1, a2"
plot "./data2.dat" using 5:3 with lines title "a1", "./data2.dat" using 5:4 with lines title "a2"