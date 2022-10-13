set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/ECS_tests/Resource_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/Resource_class_tests.cpp
    ${SRC_ROOT}/GameClock_resource_tests.cpp
)

create_test(
    TEST_NAME Resource_class_tests
    TEST_SRC ${TEST_SRC_ROOT}
    TEST_DEPS ${PROJECT_NAME}_ecs ${PROJECT_NAME}_gameSharedResources
)
