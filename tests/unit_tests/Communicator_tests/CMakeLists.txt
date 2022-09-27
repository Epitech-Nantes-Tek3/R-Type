## Setting Variables ##
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/Communicator_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/entrypoint_tests.cpp
)

## Documented Example ##
create_test(
    ## First, the name of the test ##
    TEST_NAME entrypoint_tests
    ## Second, the sources for the test ##
    TEST_SRC ${TEST_SRC_ROOT}
    ## Last, the depenancies (necessary libraries) ##
    TEST_DEPS ${PROJECT_NAME}_communicator
)