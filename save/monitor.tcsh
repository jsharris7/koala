touch /home/cniu/koala/save/running
while ( ! -e /home/cniu/koala/save/stop )
    bjobs -d | tail -n +2 >> /home/cniu/koala/save/finished.jobs
    bjobs -dl >> /home/cniu/koala/save/finished.details
    if ( -e /home/cniu/koala/save/stopped ) then
        rm /home/cniu/koala/save/stopped
    endif
    sleep 3600
end
rm /home/cniu/koala/save/stop /home/cniu/koala/save/running
touch /home/cniu/koala/save/stopped
