#!/usr/bin/env bash

echo -e "login\tdate/time\t\t\trealname"
for i in $(who | cut -d \  -f 1)
do
	real_name=`getent passwd $i | cut -d : -f 5`
	dt=`lastlog -u $i | { read; cut -c44- ;}`
	echo -e "${i}\t${dt}\t${real_name}"
done
