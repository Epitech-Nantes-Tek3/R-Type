set(TARGET r-type_client)

set(SRC_ROOT ${PROJECT_SOURCE_DIR}/Client)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/Client)

set(SRC
    ${SRC_ROOT}/main.cpp
    ${SRC_ROOT}/ClientRoom.cpp

    ${SRC_ROOT}/ClientRoom.hpp
)

add_executable(${TARGET} ${SRC})

set_property(TARGET ${TARGET} PROPERTY MSVC_RUNTIME_LIBRARY "")

set_target_properties(${TARGET}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

target_link_libraries(${TARGET}
	CONAN_PKG::sfml
    ${PROJECT_NAME}_transisthor
    ${PROJECT_NAME}_error
)

target_include_directories(${TARGET}
    PUBLIC ${CONAN_INCLUDE_DIRS_SFML}
    PUBLIC ${INC_ROOT}
    PUBLIC ${PROJECT_NAME}_transisthor
    INTERFACE ${PROJECT_NAME}_error
    PRIVATE ${SRC_ROOT}
)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)