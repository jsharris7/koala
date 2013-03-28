#! /bin/tcsh

if ( -e data-mur ) then
	rm data-mur
endif

foreach i ( `ls *out` )
	set V = `grep volume $i | awk '{print $4}'`
	set E = `grep ! $i | awk '{print $5}'`
	echo "$V	$E" >> data-mur
end

mur-fit << EOF
data-mur
murfit
EOF

rm data-mur
