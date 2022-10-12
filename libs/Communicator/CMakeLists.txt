set(INC_ROOT ${PROJECT_SOURCE_DIR}/libs)
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/Communicator)

set(TARGET ${PROJECT_NAME}_communicator)

set(SRC
    ${SRC_ROOT}/Client.cpp
    ${SRC_ROOT}/Communicator.cpp
    ${SRC_ROOT}/Sender.cpp
    ${SRC_ROOT}/Receiver.cpp

    ${SRC_ROOT}/Client.hpp
    ${SRC_ROOT}/Communicator.hpp
    ${SRC_ROOT}/Sender.hpp
    ${SRC_ROOT}/Receiver.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PUBLIC ${CONAN_INCLUDE_DIRS_BOOST}
    PRIVATE ${PROJECT_NAME}_transisthor
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
	CONAN_PKG::boost
    ${PROJECT_NAME}_transisthor
)

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)