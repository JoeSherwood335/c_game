#!/bin/bash

lib_name="$1"
lib_name_="$1_"

shared_libs="../include"

bin_folder="./$lib_name/bin"

lib_folder="./$lib_name"

src_folder="./$lib_name/src"

echo "lib_name=$lib_name"
echo "src_folder=$src_folder"
echo "shared_libs=$shared_libs"

set -e

if [ ! -e "$lib_folder" ]; then
  echo "Making $lib_folder..." 
  mkdir $lib_folder 
fi

if [ ! -e "$bin_folder" ]; then
  echo "Making $bin_folder..." 
  mkdir $bin_folder 
fi

if [ ! -e "$src_folder" ]; then
  echo "Making $src_folder..." 
  mkdir $src_folder 
fi

h_file="$src_folder/$lib_name.h"
c_file="$src_folder/$lib_name.c"

touch $c_file
touch $h_file

cp "$h_file" $shared_libs 

echo ""
echo "***** copy in include *****"
echo "#include \"$lib_name.h\""
echo "***** end include *****"
echo ""
echo "****** .gitignore *******"
echo ""
echo "include/$lib_name.h"
echo ""
echo "****** end ignore *******"
echo ""
echo "***** copy in makeFile *****"
echo ""
echo "\$(LIB)/lib_$lib_name.a: c_libraries/$lib_name/src/$lib_name.c"
echo " @echo \"Building Library $lib_name\""
echo " @\$(CXX) \$(CXX_L_FLAGS) -I \$(INCLUDE) $^ -o c_libraries/$lib_name/bin/lib_$lib_name.o"
echo " @ar rsc $@ c_libraries/$lib_name/bin/lib_$lib_name.o"
echo " @cp c_libraries/$lib_name/src/$lib_name.h \$(INCLUDE)/$lib_name.h"
echo "***** end makeFile *****"


