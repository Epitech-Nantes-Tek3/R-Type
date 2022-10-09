## Setting Variables ##
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/LibsClient_tests/CreateEntitiesFunctions_tests)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/LibsClient_tests/CreateEntitiesFunctions_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/CreateAllyProjectile_test.cpp
    ${SRC_ROOT}/CreateEnemyProjectile_test.cpp
    ${SRC_ROOT}/CreateProjectile_test.cpp
    ${SRC_ROOT}/CreatePlayer_test.cpp
    ${SRC_ROOT}/CreateEnemy_test.cpp
    ${SRC_ROOT}/CreateObstacle_test.cpp
)

## Documented Example ##
create_test(
    ## First, the name of the test ##
    TEST_NAME create_entities_tests
    ## Second, the sources for the test ##
    TEST_SRC ${TEST_SRC_ROOT}
    ## Last, the depenancies (necessary libraries) ##
    TEST_DEPS ${PROJECT_NAME}_createEntitiesFunctions
    ## In this case none, otherwise add TEST_DEPS ${DEPENDANCY_NAME}
)
