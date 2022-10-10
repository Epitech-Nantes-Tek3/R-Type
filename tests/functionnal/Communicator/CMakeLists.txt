set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/functionnal/Communicator)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/functionnal/Communicator)

set (TARGET ${PROJECT_NAME}_sender_tests)

set (SRC
    ${SRC_ROOT}/sender_tests.cpp
)

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC ${PROJECT_NAME}_communicator
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
)

set (TARGET ${PROJECT_NAME}_receiver_tests)

set (SRC
    ${SRC_ROOT}/receiver_tests.cpp
)

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC ${PROJECT_NAME}_communicator
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
)

set (TARGET ${PROJECT_NAME}_communicator_tests)

set (SRC
    ${SRC_ROOT}/communicator_tests.cpp
)

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC ${PROJECT_NAME}_communicator
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
)

set (TARGET ${PROJECT_NAME}_communicator_switch_tests)

set (SRC
    ${SRC_ROOT}/communicator_switch_tests.cpp
)

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC ${PROJECT_NAME}_communicator
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
)

set (TARGET ${PROJECT_NAME}_communicator_send)

set (SRC
    ${SRC_ROOT}/communicator_send.cpp
)

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC ${PROJECT_NAME}_communicator
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
)