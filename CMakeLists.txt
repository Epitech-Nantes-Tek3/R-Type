# Specify the required version of cmake
cmake_minimum_required(VERSION 3.17)

# Set the project name (R-Type) and the language used (c++)
project(R-Type LANGUAGES CXX)

# Set the c++ version and set this version required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add ./cmake to the module and prefix path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Include .cmake file to be used with this one
include(DetectCompiler)

# Add subdirectory to find there CMakeLists.txt
add_subdirectory(Server)
add_subdirectory(Client)
add_subdirectory(libs)

# Create executables and set there sources
add_executable(r-type_client ${SRC_CLIENT})
add_executable(r-type_server ${SRC_SERVER})

# Add properties to executables
set_property(TARGET r-type_client PROPERTY MSVC_RUNTIME_LIBRARY "")
set_target_properties(r-type_client r-type_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

# Link libraries to executables
target_link_libraries(r-type_client
	CONAN_PKG::sfml
)

# Target include directories from libraries
target_include_directories(r-type_client PUBLIC
	${CONAN_INCLUDE_DIRS_SFML}
)

# Setup and include conan to build dependencies
include(build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
