#!/bin/bash

test_path=$2*.in
mkdir _temp

for f in $test_path
do
	f_pathless=`basename $f`
	f_extless="${f%.*}"
	filename="${f_pathless%.*}"
	echo -n "Processing	$filename		"
	my_out_path=_temp/$filename.out
	my_err_path=_temp/$filename.err
	$1 < $f > $my_out_path 2> $my_err_path
	if diff $my_out_path $f_extless.out > /dev/null 2>&1
	then
		echo -n "OUT-OKE	"
	else
		echo -n "OUT-BAD	"
	fi
	if diff $my_err_path $f_extless.err > /dev/null 2>&1
	then
		echo "ERR-OKE	"
	else
		echo "ERR-BAD	"
	fi
	# if valgrind --error-exitcode=1 ./energia < $f > /dev/null 2>&1
	# then
	# 	echo "MEM-OKE"
	# else
	# 	echo "MEM-BAD"
	# fi
done

rm -rf _temp
