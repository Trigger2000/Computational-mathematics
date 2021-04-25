set terminal svg enhanced size 1000 1000

set output "plot_xyz_rk1.svg"
set xlabel "x"
set ylabel "y"
set zlabel "z"
splot "./data1.dat" using 3:4:5 with lines

set output "plot_u_rk1.svg"
set xlabel "t"
set ylabel "u"
plot "./data1.dat" using 1:2 with lines

set output "plot_xyz_rk2.svg"
set xlabel "x"
set ylabel "y"
set zlabel "z"
splot "./data2.dat" using 3:4:5 with lines

set output "plot_u_rk2.svg"
set xlabel "t"
set ylabel "u"
plot "./data2.dat" using 1:2 with lines

set output "plot_xyz_rk3.svg"
set xlabel "x"
set ylabel "y"
set zlabel "z"
splot "./data3.dat" using 3:4:5 with lines

set output "plot_u_rk3.svg"
set xlabel "t"
set ylabel "u"
plot "./data3.dat" using 1:2 with lines

set output "plot_xyz_rk4.svg"
set xlabel "x"
set ylabel "y"
set zlabel "z"
splot "./data4.dat" using 3:4:5 with lines

set output "plot_u_rk4.svg"
set xlabel "t"
set ylabel "u"
plot "./data4.dat" using 1:2 with lines