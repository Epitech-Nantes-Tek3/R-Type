set (INC_ROOT ${PROJECT_SOURCE_DIR}/libs)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/libs/Communicator)

set (TARGET ${PROJECT_NAME}_communicator)

set (SRC
    ${SRC_ROOT}/entrypoint.cpp
    ${SRC_ROOT}/Client.cpp
    ${SRC_ROOT}/Communicator.cpp
    ${SRC_ROOT}/Sender.cpp

    ${SRC_ROOT}/entrypoint.hpp
    ${SRC_ROOT}/Client.hpp
    ${SRC_ROOT}/Communicator.hpp
    ${SRC_ROOT}/Sender.hpp
)

add_library(${TARGET} ${SRC})
# ${Boost_LIBRARIES})
target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PUBLIC ${CONAN_INCLUDE_DIRS_BOOST}
    # ${CONAN_INCLUDE_DIRS_BOOST} ${CONAN_INCLUDE_DIRS_ASIO}
    PRIVATE ${SRC_ROOT}
)