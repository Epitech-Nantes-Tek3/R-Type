
## Setting Variables ##
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/ECS_tests/Entity_tests)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/ECS_tests/Entity_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/Entity_class_tests.cpp
)

## Documented Example ##
create_test(
    ## First, the name of the test ##
    TEST_NAME Entity_class_tests
    ## Second, the sources for the test ##
    TEST_SRC ${TEST_SRC_ROOT}
    ## Last, the depenancies (necessary libraries) ##
    TEST_DEPS ${PROJECT_NAME}_ecs
    ## In this case none, otherwise add TEST_DEPS ${DEPENDANCY_NAME}
)
