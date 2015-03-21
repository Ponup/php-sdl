#!/bin/sh
for i in *.c *.h examples/*.php tests/*.phpt
do
	j=$(basename $i)
	if [ $j != config.h ]; then
		grep -q "'$j'" package.xml || echo Missing $i
	fi
done

