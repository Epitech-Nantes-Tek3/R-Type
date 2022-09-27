## Minimum version of CMake ##
cmake_minimum_required(VERSION 3.17)

## Project Name and the development language ##
project(R-type LANGUAGES CXX)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

## Set the minimal version of the language and make it required ##
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

## Add the flags for the compilation ##
add_compile_options(
    "-Wall" "-Wextra" "-Werror" "-pedantic" "-Wpointer-arith" "-fpic"
)

## TESTING ##
option(TESTING OFF)
if (TESTING)
    enable_testing()
    add_compile_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    add_link_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    add_subdirectory(tests)
endif()

## Looking for others CmakeLists.txt ##
add_subdirectory(Server)
add_subdirectory(Client)

## Create the needed executables ##
add_executable(r-type_client ${SRC_CLIENT})
add_executable(r-type_server ${SRC_SERVER})

## Put the executable to the project's root ##
set_target_properties(r-type_client r-type_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)