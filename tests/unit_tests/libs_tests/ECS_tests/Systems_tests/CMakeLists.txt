
## Setting Variables ##
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/ECS_tests/Systems_tests)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/ECS_tests/Systems_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/Velocity_System_tests.cpp
)

## Documented Example ##
create_test(
    ## First, the name of the test ##
    TEST_NAME Systems_tests
    ## Second, the sources for the test ##
    TEST_SRC ${TEST_SRC_ROOT}
    ## Last, the depenancies (necessary libraries) ##
    TEST_DEPS ${PROJECT_NAME}_gameSystems
    ## In this case none, otherwise add TEST_DEPS ${DEPENDANCY_NAME}
)
