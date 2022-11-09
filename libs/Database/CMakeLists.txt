set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/Database)

set(TARGET ${PROJECT_NAME}_database)

set(SRC
    ${SRC_ROOT}/Database.cpp
    ${SRC_ROOT}/Database.hpp
)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_library(${TARGET} SHARED ${SRC})
elseif(MSVC)
    add_library(${TARGET} ${SRC})
else()
    message(WARNING "Unknown compiler type, compilation may not work as expected")
endif()

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PRIVATE ${SRC_ROOT}
    PRIVATE ${CONAN_INCLUDE_DIRS_SQLITE3}
)

target_link_libraries(${TARGET}
    CONAN_PKG::sqlite3
)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

install(TARGETS ${TARGET} DESTINATION lib)