cmake_minimum_required(VERSION 3.16.0)

project(R-Type LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add ./cmake to the module path
# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)
# list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# include(build/conanbuildinfo.cmake)

# if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
#   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
#   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
#                 "${CMAKE_BINARY_DIR}/conan.cmake"
#                 TLS_VERIFY ON)
# endif()

# include(${CMAKE_BINARY_DIR}/conan.cmake)

# conan_cmake_configure(REQUIRES sfml/2.5.1
#                       GENERATORS cmake_find_package cmake)

# conan_cmake_autodetect(settings)

# conan_cmake_install(PATH_OR_REFERENCE .
#                     BUILD missing
#                     REMOTE conancenter
#                     SETTINGS ${settings})

# include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

# find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)

include(DetectCompiler)

add_subdirectory(Server)
add_subdirectory(Client)

add_executable(r-type_client ${SRC_CLIENT})
add_executable(r-type_server ${SRC_SERVER})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(r-type_client PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# target_link_libraries(r-type_client ${CONAN_LIBS})

set_target_properties(r-type_client r-type_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)
