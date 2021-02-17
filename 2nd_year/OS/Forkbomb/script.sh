# Simple bash-script for grabbing info about amount of processes [ Linux ]

#!/bin/bash
while true
do
	ps -alx | wc -l >> plot.txt
done
