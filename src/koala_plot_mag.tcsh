#! /bin/tcsh
# 
# koala_plot_mag.tcsh
#
# This code reads atomic coordinates from CONTCAR,
# magnetic moments from OUTCAR. Then it plots static 
# images using gnuplot viewed from different angles,
# and convert to animation gif using ImageMagick.
#
# Author: Changning Niu (cniu@ncsu.edu)
# Updated: 03-29-2013

# User input:
# Scaler for magnetic moments
set scale = 0.5

# Extract dx dy dz (magnetic moments)
set nElement = `awk 'NR==7' CONTCAR | wc -w`
set nAtom = `sed -n '/Direct/,$p' CONTCAR | wc -l | awk '{print $1/2-1}'`
set nLine = `echo "23+3*$nAtom" | bc`
set nLine1 = `echo "$nLine+1" | bc`
tail -1000 OUTCAR | grep -A $nLine "magnetization (x)" | tail -$nLine1 > mag.tmp1
echo -n "" > mag.tmp2
foreach i ( `seq 1 $nAtom` )
    echo -n `grep " $i   " mag.tmp1 | awk '{print $5}'` >> mag.tmp2
    echo >> mag.tmp2
end
mv mag.tmp2 mag.tmp1
# Multiply by scale
awk '{print $1*'$scale',$2*'$scale',$3*'$scale'}' mag.tmp1 > mag.tmp2
mv mag.tmp2 mag.tmp1

# Extract x y z from CONTCAR
koala_dire2cart CONTCAR
tail -$nAtom CONTCAR.cart > mag.tmp2
cp mag.tmp2 mag.atoms
# Create x y z dx dy dz
paste mag.tmp2 mag.tmp1 > mag.tmp
rm mag.tmp1 mag.tmp2

# Divide into files for each element
foreach i ( `seq 1 $nElement` )
    set n = `awk 'NR==7 {print $'$i'}' CONTCAR`
    sed -n '1,'$n'p' mag.tmp > mag.$i
    awk 'NR==6 {print $'$i'}' CONTCAR > mag.atom$i
    sed -n '1,'$n'p' mag.atoms >> mag.atom$i
    set n1 = `echo "$n+1" | bc`
    sed -n ''$n1',$p' mag.tmp > mag.tmp1
    sed -n ''$n1',$p' mag.atoms > mag.tmp2
    mv mag.tmp1 mag.tmp
    mv mag.tmp2 mag.atoms
end
rm mag.tmp mag.atoms

# Plot using Gnuplot.
cat > gnu.script << EOF
splot 'mag.1' u 1:2:3:4:5:6 with vectors notitle lc rgb 'red', \
      'mag.2' u 1:2:3:4:5:6 with vectors notitle lc rgb 'black', \
      'mag.3' u 1:2:3:4:5:6 with vectors notitle lc rgb 'blue',\
      'mag.4' u 1:2:3:4:5:6 with vectors notitle lc rgb 'purple',\
      'mag.atom1' w circles title columnheader(1)lc rgb 'red',\
      'mag.atom2' w circles title columnheader(1)lc rgb 'black',\
      'mag.atom3' w circles title columnheader(1)lc rgb 'blue',\
      'mag.atom4' w circles title columnheader(1)lc rgb 'purple'

set term png size 640,640
set lmargin 0
set rmargin 0
set tmargin 0
set bmargin 0
do for [ii=1:36] {
    set output sprintf('mag_frame%03.0f.png',ii)
    set view 60,10*ii
    rep
}
EOF
gnuplot < gnu.script
rm gnu.script
convert mag_frame* mag.gif
rm mag_frame* mag.? mag.atom?
