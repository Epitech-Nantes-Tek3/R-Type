#!/usr/bin/bash

# Function to test exit status of a command.
# It exits if the command failed.
function testExitStatus()
{
    if [ $1 -ne 0 ]
    then
        echo "$2 failed"
        exit 1
    else
        echo "$2 successed"
    fi
}

# Create build directory
mkdir -p build
testExitStatus $? "mkdir"

# Update path into build directory
cd build
testExitStatus $? "cd"

# Install conan dependencies
conan install .. --build=missing -s compiler.libcxx=libstdc++11 -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
testExitStatus $? "conan install dependencies"

# Configure cmake
cmake -DCMAKE_BUILD_TYPE=Debug ..
testExitStatus $? "cmake config"

# Build using cmake
cmake --build  . -- -j
testExitStatus $? "cmake build"
