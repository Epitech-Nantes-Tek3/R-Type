cmake_minimum_required(VERSION 3.16.0)

project(R-Type LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(conanbuildinfo.cmake)
conan_basic_setup()

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

include(DetectCompiler)

add_subdirectory(Server)
add_subdirectory(Client)


add_executable(r-type_client ${SRC_CLIENT})
add_executable(r-type_server ${SRC_SERVER})

target_link_libraries(r-type_client ${SFML_LIBRARIES})
set_target_properties(r-type_client r-type_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)
