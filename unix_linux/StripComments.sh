#!/usr/bin/env bash
# remove comments from script/.py

[[ $# -ne 1 ]] && (echo "usage: ./$0 file_name" ; exit 1)

if [[ -x $1 ]]; then

	echo -e "Before:\n$(cat $1)\n"
	echo "After:"
	#sed -e '2,$s/#.*$//' -e 's/[ ]*$//' -e '/^$/d' -i $1
	sed -e '/^#[^!]/d' -e '2,$s/#.*$//' -e 's/[ /t]*$//' $1
	# last sed command removes trailing tabs and whitespaces
else
	echo "given argument isn't a file or script"
fi
