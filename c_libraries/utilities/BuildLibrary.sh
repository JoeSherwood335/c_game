#!/bin/bash

new_folder="bin/$(date +"%FT%H%M%z")"
lib_name=lib_utilities


[ -d "$new_folder" ] && echo "" || mkdir $new_folder

gcc -c src/*.c -o $new_folder/$lib_name.o

ar rsc $new_folder/$lib_name.a $new_folder/$lib_name.o

cp src/*.h $new_folder/
