set (INC_ROOT ${PROJECT_SOURCE_DIR}/libs)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/Communicator)

set (TARGET ${PROJECT_NAME}_communicator)

set (SRC
    ${SRC_ROOT}/entrypoint.cpp
    ${SRC_ROOT}/Client.cpp
    ${SRC_ROOT}/Communicator.cpp

    ${SRC_ROOT}/entrypoint.hpp
    ${SRC_ROOT}/Client.hpp
    ${SRC_ROOT}/Communicator.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PRIVATE ${SRC_ROOT}
)