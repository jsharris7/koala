#! /bin/tcsh
# 
# koala_espr_mur.tcsh
#
# This code fits murnaghan EOS for ESPRESSO 
# calculations.
#
# Author: Changning Niu (cniu@ncsu.edu)
# Updated: 03-29-2013

if ( -e data-mur ) then
	rm data-mur
endif

foreach i ( `ls *out` )
	set V = `grep volume $i | awk '{print $4}'`
	set E = `grep ! $i | awk '{print $5}'`
	echo "$V	$E" >> data-mur
end

mur_fit << EOF
data-mur
mur_fit.out
EOF

rm data-mur
