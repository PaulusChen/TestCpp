#!/bin/sh

if test ! -e SysLibInclude; then
    ln -s /usr/include ./SysLibInclude
fi


if test ! -e SysLocLibInclude; then
    ln -s /usr/local/include ./SysLocLibInclude
fi
PROJECT_HOME=`pwd`

cd ${PROJECT_HOME}

ProjectRootDir=`pwd`
buildDir="build"

if [ ${1}x = "clean"x ]
then
    echo "Removeing generated files..."
    git clean -xdf
    exit 0
fi

# ./automake.sh Debug
#./ automake.sh Release

if test ! -e build; then
    mkdir build
fi

cd build
cmake -DCMAKE_BUILD_TYPE={1} ..
cd ..
gtags
