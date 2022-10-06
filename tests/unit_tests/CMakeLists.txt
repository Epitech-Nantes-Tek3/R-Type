
## Setting Variables ##
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/very_basic_test.cpp
)

## Documented Example ##
create_test(
    ## First, the name of the test ##
    TEST_NAME very_basic_test
    ## Second, the sources for the test ##
    TEST_SRC ${TEST_SRC_ROOT}
    ## Last, the depenancies (necessary libraries) ##
    ## In this case none, otherwise add TEST_DEPS ${DEPENDANCY_NAME}
)

add_subdirectory(Communicator_tests)
add_subdirectory(Transisthor_tests)
add_subdirectory(libs_tests)