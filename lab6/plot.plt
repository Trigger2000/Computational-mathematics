set terminal svg enhanced size 1000 1000

set output "plot_model.svg"
set xlabel "x"
set ylabel "y"
plot "./data1.dat" using 1:2 with lines

set output "plot_task.svg"
set xlabel "x"
set ylabel "y"
plot "./data2.dat" using 1:2 with lines