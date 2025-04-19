#!/bin/bash
lib_name="$1"

bin_folder="./$lib_name/bin"

src_folder="./$lib_name/src"

project_lib_folder="../lib"

project_include_folder="../include"

current_time="$(date +"%F_%H:%M")"

echo "lib_name=$lib_name"
echo "src_folder=$src_folder"
echo "project_lib_folder=$project_lib_folder"
echo "project_include_folder=$project_include_folder"
echo "current_time=$current_time"

set -e

if [ ! -e "$bin_folder" ]; then
	echo "$bin_folder not found"
    echo "exiting"	
elif [ ! -e "$src_folder" ]; then
	echo "$src_folder not found"
    echo "exiting"	
elif [ -f "$bin_folder/lib_$lib_name_$current_time.o" ]; then
    echo "up to date!"
else	
    echo "Compiling..."	


gcc -c $src_folder/$lib_name.c -o $bin_folder/lib_$lib_name_$current_time.o

ar rsc $project_lib_folder/lib_$lib_name.a $bin_folder/lib_$lib_name_$current_time.o

cp $src_folder/*.h $project_include_folder
    echo "Completed"	
fi
