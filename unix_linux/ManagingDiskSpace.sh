#!/usr/bin/env bash


echo "Select max depth ([max] to max)"
while : ; do
	read maxdepth
	case $maxdepth in
		[0-9]|[0-9]) ARGS+="-maxdepth $maxdepth " && break ;;
		max) break;;
		*) echo 'Please enter [one,two]-digit number or max'
esac ; done;

ARGS+="-type f -size +100k"

# unzip

for i in $(find $HOME $ARGS)
do
	echo "file: $(basename $i)"
	echo "[i]gnore/[d]elete/[c]ompress (Ctrl-c to quit)"
	read prompt
	case $prompt in
		[d]*)	echo "deleting..."
			rm $i
			echo "Deleted file: $i" >> ${HOME}/.cache/mds.log
			;;
		[c]*)	echo "compressing to ${i}.tar.gz ..."
			# tar czf ${i}.tar.gz $i
			echo "Compressed file: $i" >> ${HOME}/.cache/mds.log
			;;
		*) echo "File skipped..."
	esac
done

# zip
