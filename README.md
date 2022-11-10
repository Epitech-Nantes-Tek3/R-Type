# R-Type
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) ![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
 ![GitHub Actions](https://img.shields.io/badge/github%20actions-%232671E5.svg?style=for-the-badge&logo=githubactions&logoColor=white) ![CodeCov](https://img.shields.io/badge/codecov-%23ff0077.svg?style=for-the-badge&logo=codecov&logoColor=white)
***
## Introduction

The goal of the Epitech R-Type project is to implement a multithreaded server and a graphical client for a game called R-Type, using an engine of our own design.

The project is composed of two parts: the server and the client, both in C++.

It uses three libraries:
* SFML: The library used to display.
* Boost: The library used to manage communication, threads and processes.
* SQLite3: The library used to manage the storage.

It is compatible on Linux and Windows.

## Prerequisites

To build our R-Type project, you will need CMake 3.17.0 Compiler, C++ 20 and Conan.
****
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

You can see the UDP Protocol used in the project right [here](https://amazing-partridge-567.notion.site/R-Type-Documentations-On-est-que-4-de59851ea5e64808a3c3d9f145a960a9)


## Thank for reading

Feel free to read the CONTRIBUTING.md

Do not hesitate to contact any member for any questions or remarks.

* Mail -> firstname.lastname@epitech.eu

## Authors

* **Tom Duval-Mahe, Quentin Camilleri, Thomas Prud'homme, Nathan Rousseau, Lucas Tesnier**
