set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/ECS_tests/Systems_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/Movement_System_tests.cpp
    ${SRC_ROOT}/Decrease_LifeTime_System_tests.cpp
    ${SRC_ROOT}/Death_System_tests.cpp
    ${SRC_ROOT}/LifeTimeDeath_tests.cpp
    ${SRC_ROOT}/Death_Life_System_tests.cpp
    ${SRC_ROOT}/Collidable_system_test.cpp
    #${SRC_ROOT}/EnemyGoRandom_System_test.cpp
    ${SRC_ROOT}/ShootEnemy_system_test.cpp
)

create_test(
    TEST_NAME Systems_tests
    TEST_SRC ${TEST_SRC_ROOT}
    TEST_DEPS ${PROJECT_NAME}_gameSystems
)
