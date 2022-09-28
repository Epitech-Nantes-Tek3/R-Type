## Setting Variables ##
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/Communicator_tests)

create_test(
    TEST_NAME entrypoint_tests
    TEST_SRC ${SRC_ROOT}/entrypoint_tests.cpp
    TEST_DEPS ${PROJECT_NAME}_communicator
)

create_test(
    TEST_NAME client_tests
    TEST_SRC ${SRC_ROOT}/Client_tests.cpp
    TEST_DEPS ${PROJECT_NAME}_communicator
)

create_test(
    TEST_NAME communicator_tests
    TEST_SRC ${SRC_ROOT}/Communicator_tests.cpp
    TEST_DEPS ${PROJECT_NAME}_communicator
)

create_test(
    TEST_NAME receiver_tests
    TEST_SRC ${SRC_ROOT}/Receiver_tests.cpp
    TEST_DEPS ${PROJECT_NAME}_communicator
)