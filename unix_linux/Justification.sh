#!/usr/bin/env bash

[[ $# -eq 0 ]] && echo "Enter your text: (Ctrl-d when done)"

line=$(cat $1)
echo "Enter line-width:"
read tmp
for i in "${line}"; do
	printf "%${tmp}s\n" $i
done
