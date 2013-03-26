#! /bin/tcsh                                                                                                                                    

### User define:

#echo -n "Enter the plot title: "
#set TITLE = "$<"

#####################################

set N = `awk 'NR==6 {print $3+6}' DOSCAR`
set Ef = `awk 'NR==6 {print $4}' DOSCAR`

sed -n 7,${N}p DOSCAR | awk '{print $1-('$Ef'),$2}' > TDOS.dat

gnuplot << EOF
set autoscale # scale axes automatically
set xtic auto # set xtics automatically
set ytic auto # set ytics automatically
set title "'TITLE'" # set title
set xlabel "Energy (eV)" # set x-label
set ylabel "DOS" # set y-label
set xrange [-5:5]
set size 1,.5
set terminal postscript portrait
set output "TDOS.ps"
plot 'TDOS.dat' title 'Total DOS' with lines
EOF

convert TDOS.ps TDOS.png
rm TDOS.ps
