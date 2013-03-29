#! /bin/tcsh
# 
# koala_emto_mur.tcsh
#
# This code fit murnaghan EOS for EMTO-CPA results.
#
# Author: Changning Niu (cniu@ncsu.edu)
# Updated: 03-29-2013

if ( -e data-mur ) then
    rm data-mur
endif

foreach i ( `ls` )
    if ( -d $i ) then
        set r = `grep "Total-PBE" $i/output* | awk '{print $7}'`
        set V = `echo "scale=6; 4.18879*$r*$r*$r" | bc`
        echo -n "$V " >> data-mur
        grep "Total-PBE" $i/output* | awk '{print $4}'` >> data-mur
    endif
end

mur_fit << EOF
data-mur
mur_fit.out
EOF

rm data-mur
