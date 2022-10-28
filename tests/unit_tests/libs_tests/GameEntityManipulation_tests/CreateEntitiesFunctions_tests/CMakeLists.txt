set(SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/GameEntityManipulation_tests/CreateEntitiesFunctions_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/CreateAlliedProjectile_test.cpp
    ${SRC_ROOT}/CreateEnemyProjectile_test.cpp
    ${SRC_ROOT}/CreateProjectile_test.cpp
    ${SRC_ROOT}/CreatePlayer_test.cpp
    ${SRC_ROOT}/CreateEnemy_test.cpp
    ${SRC_ROOT}/CreateObstacle_test.cpp
    ${SRC_ROOT}/CreateEnemyRandom_test.cpp
    ${SRC_ROOT}/CreateBackGround_tests.cpp
    ${SRC_ROOT}/CreateButton_tests.cpp
)

create_test(
    TEST_NAME create_entities_tests
    TEST_SRC ${TEST_SRC_ROOT}
    TEST_DEPS ${PROJECT_NAME}_RTypeLogicCreateEntitiesFunctions ${PROJECT_NAME}_RTypeLogicGlobal ${PROJECT_NAME}_SFMLGraphicECS ${PROJECT_NAME}_RTypeLogicButtonManipulation
)
