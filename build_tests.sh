#!/usr/bin/bash

mkdir -p build; cd build && conan install .. --build=missing -s compiler.libcxx=libstdc++11 -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True && cmake -DCMAKE_BUILD_TYPE=Debug -DTESTING=On .. && cmake --build . -- -j && ctest --output-on-failure

#Create a HTML file to visualize coverage
cd .. && gcovr --html coverage.html