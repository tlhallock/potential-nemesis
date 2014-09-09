#!/bin/bash


python get_distances.py  10 50
sleep 1
python get_distances.py  3  20
sleep 1
python get_distances.py  3  5
sleep 1
python get_distances.py  10  2

./remove_bad_ones.sh

translate.py
cp *.json.dst.out known_distances/
mv *json* examples/

find `pwd`/known_distances/ -type f > examples/list.txt

