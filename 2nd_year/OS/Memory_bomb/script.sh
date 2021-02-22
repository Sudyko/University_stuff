# Simple bash-script for grab memory statistics [ Linux ]
# Left col. - Used Memory
# Right col. - Free Memory

#!/bin/bash
while true
do
	free -m | awk '{print $3, $4}' | head -2 | tail -1 >> plot.txt
done