# Simple bash-script for grab amount of processes [ Linux ]

#!/bin/bash
while true
do
	ps -alx | wc -l >> plot.txt
done
