#!/bin/bash

for file in $(grep -r 'You have exceeded your rate-limit for this API.' . | grep -v remove_bad_ones.sh | tr ':' ' ' | awk ' { print $1 } ' )
do
	rm -v $file
	rm -v $file.locs
done

