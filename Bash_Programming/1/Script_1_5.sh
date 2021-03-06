#!/bin/bash

#Created by Deep C. Patel-1401010

clear

echo "Enter Source Directory-1:"
read dir1

echo "Enter Source Directory-2:"
read dir2

echo "Enter Destination Directory:"
read dir3

for f in $dir1/*						#Iterating for files in folder
do
	f12=$( basename "/$f" )						#Extracting file name from path
		
	if [ -f "$dir2/$f12" ]					#Checking whether path(file path) exists or not
	then 
		
		if [ "$dir1/$f12" -nt "$dir2/$f12" ]		#Comparing the modification date of files
		then
 			 cp "$dir1/$f12" "$dir3"
		else
			 cp "$dir2/$f12" "$dir3"
		fi

	else
		cp "$dir1/$f12" "$dir3"
	
	fi

done

for f in $dir2/*
do

	cp -n $f "$dir3"						#Copying the files and not replacing existing files in $dir3

done
	
