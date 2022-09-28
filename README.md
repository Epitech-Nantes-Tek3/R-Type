***
[![Build](https://github.com/osvegn/R-Type/actions/workflows/build.yml/badge.svg)](https://github.com/osvegn/R-Type/actions/workflows/build.yml)

[![Coding style](https://github.com/osvegn/R-Type/actions/workflows/lints.yml/badge.svg)](https://github.com/osvegn/R-Type/actions/workflows/lints.yml)

[![Mirroring](https://github.com/osvegn/R-Type/actions/workflows/mirroring.yml/badge.svg)](https://github.com/osvegn/R-Type/actions/workflows/mirroring.yml)

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
***

# R-Type

The goal of the Epitech R-Type project is to implement a multithreaded server and a graphical client for a game called R-Type, using an engine of our own design.

Composed of two parts, namely the server and the client both in C++ with the graphic library SFML for the client and boost asio for the server.

## Prerequisites

To build our R-Type project, you will need CMake 3.17.0 Compiler, C++ 20 and Conan.

## Build the program

On Linux :

You may use the build.sh or the following commands :

```bash
    cmake -B ./build -DCMAKE_BUILD_TYPE=Release
    cmake --build ./build
```

On Windows :

* You may use the build.bat or the following commands :

```bash
    mkdir build
    cd build
    conan install .. --build=missing  -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
    cd ..
    cmake -B ./build -DCMAKE_BUILD_TYPE=Release
    cmake --build ./build
    "copy .\Debug\r-type_client.exe ."
    "copy .\Debug\r-type_server.exe ."
```

## Testing program
```bash
    rm -rf ./build
    cmake -B ./build -DCMAKE_BUILD_TYPE=Debug -DTESTING=ON
    cmake --build ./build
    cd ./build
    ctest --ouput-on-failure
```

## Supported Platform

The R-Type project is supported on Windows AND Linux !!


## Usefulls Links

You can see the UDP Protocol used in the project [right here](https://www.notion.so/3e9469baeb9e4ae2bf05c215babdf142?v=4047238dabd94ec6b7c035eabf6bbc31)


## Thank for reading

Feel free to read the CONTRIBUTING.md

Do not hesitate to contact any member for any questions or remarks.

* Mail -> firstname.lastname@epitech.eu

## Authors

* **Tom Duval-Mahe, Quentin Camilleri, Thomas Prud'homme, Nathan Rousseau, Lucas Tesnier**