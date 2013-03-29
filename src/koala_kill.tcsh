#! /bin/tcsh                                                                            
# 
# koala_kill.tcsh
#
# This code lists all running LSF jobs.
# Then let user select what to kill.
# Then kill the selected jobs.
#
# Author: Changning Niu (cniu@ncsu.edu)
# Updated: 03-29-2013

if ( ! -d ~/.koala ) then
    mkdir ~/.koala
endif

cat > ~/.koala/kill.tmp << EOF   
#### Any jobs left will be killed! ####
EOF
bjobs >> ~/.koala/kill.tmp   # tmpe jobs in a file
vim ~/.koala/kill.tmp        # let user choose jobs to kill
echo "These jobs will be killed:"
cat ~/.koala/kill.tmp        # give user last change to abort
echo -n "Are you sure? (y or n):"
set kill = $<
if ( $kill == y ) then  # kill selected jobs
    set id = `awk '{print $1}' ~/.koala/kill.tmp`
    foreach i ( $id )
        set test = `echo $i | grep "^[0-9]"`
        if ( $test ) then
            bkill $i
        endif
    end
endif

rm ~/.koala/kill.tmp         # delete the file
