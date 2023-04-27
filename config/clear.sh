#!/usr/bin/bash

for DIRECTORY in "$@"
do
	if [[ -d "$DIRECTORY" ]]
	then
		find "$DIRECTORY/" -mindepth 1 -exec rm -rf {} +
	else
		echo "$DIRECTORY is not a directory!"
	fi
done