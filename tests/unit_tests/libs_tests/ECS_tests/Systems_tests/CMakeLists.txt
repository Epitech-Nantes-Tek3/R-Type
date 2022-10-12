
## Setting Variables ##
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/ECS_tests/Systems_tests)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/ECS_tests/Systems_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/Movement_System_tests.cpp
    ${SRC_ROOT}/Decrease_LifeTime_System_tests.cpp
    ${SRC_ROOT}/Death_System_tests.cpp
    ${SRC_ROOT}/Death_LifeTime_System_tests.cpp
    ${SRC_ROOT}/Death_Life_System_tests.cpp
)

## Documented Example ##
create_test(
    ## First, the name of the test ##
    TEST_NAME Systems_tests
    ## Second, the sources for the test ##
    TEST_SRC ${TEST_SRC_ROOT}
    ## Last, the depenancies (necessary libraries) ##
    TEST_DEPS ${PROJECT_NAME}_gameSystems
    # TEST_DEPS ${PROJECT_NAME}_ClientSystems
    # TEST_DEPS ${PROJECT_NAME}_createEntitiesFunctions
    ## In this case none, otherwise add TEST_DEPS ${DEPENDANCY_NAME}
)
