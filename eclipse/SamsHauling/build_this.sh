#!/bin/bash


rm -f archive.a


for file in $(find ../src/ | grep cpp$ )
do
        echo $file ;
        outname=$(basename $file).o
        
        c="g++ -std=c++11 -pg $file -I/work/potential-nemesis/eclipse/SamsHauling/src -c -o $outname"
        
        if [[ -e $outname ]]
        then
                outtime=$(stat -c "%Y" $outname)
                srctime=$(stat -c "%Y" $file)

                if [[ $srctime -le $outtime ]]
                then
                        echo Already done!
                else
                        $c
                fi
        else
                $c
        fi
        ar rc archive.a $outname
done

g++ archive.a -pg -o samshauling -ltinyxml2

