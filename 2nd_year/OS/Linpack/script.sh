#!/bin/bash
echo "Let's start!" > out.txt
echo First stage!
for ((i = -4; i <= 4; ++i))
do
	let tmp=$i*5
	echo $tmp >> out.txt
	echo $tmp
	sudo nice -n $tmp ./a.out >> out.txt
done
echo First stage complete!
echo
echo Second stage!
for ((i = 2; i <= 32; i=$i*2))
do
	echo $i >> out.txt
	echo $i
	sudo taskset -c 1-$i ./a.out >> out.txt
done