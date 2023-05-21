#!/bin/bash

build_dir="build"

if [ ! -d "$build_dir" ]; then
    mkdir "$build_dir"
fi

cd "$build_dir"

read -p "Enter 'd' for debug mode, or any other key for release mode: " debug_mode

if [ "$debug_mode" == "d" ]; then
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make
else
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
fi

cd ..\bin
.\GradeManagementSystem.out
