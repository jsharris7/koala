#! /bin/tcsh
# 
# koala_monitor.tcsh
#
# This code first check if it is running.
# If not, it runs in background, and save
# all finished LSF jobs in a local file.
#
# Author: Changning Niu (cniu@ncsu.edu)
# Updated: 03-29-2013

if ( ! -d ~/.koala ) then
    mkdir ~/.koala
endif

if ( -e ~/.koala/running ) then
    echo "koala_monitor is already running."
else
    cat > ~/.koala/monitor.tcsh << EOF
touch ~/.koala/running
while ( ! -e ~/.koala/stop )
    bjobs -d | tail -n +2 >> ~/.koala/finished.jobs
    bjobs -dl >> ~/.koala/finished.details
    if ( -e ~/.koala/stopped ) then
        rm ~/.koala/stopped
    endif
    sleep 3600
end
rm ~/.koala/stop ~/.koala/running
touch ~/.koala/stopped
EOF
    nohup tcsh ~/.koala/monitor.tcsh &
endif
