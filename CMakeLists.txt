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
add_subdirectory(Room)
add_subdirectory(AdminPanel)

# Setup and include conan to build dependencies
include(build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

install(DIRECTORY ./assets/ DESTINATION bin/assets/)

set(CPACK_WIX_LICENSE_RTF ${PROJECT_SOURCE_DIR}/misc/windows/wix_licence.txt)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${RTYPE_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${RTYPE_MINOR_VERSION}")
set(CPACK_BUNDLE_NAME "R-Type")
include(CPack)

if(WIN32)
  install(DIRECTORY ./build/bin/ DESTINATION bin/)
endif()