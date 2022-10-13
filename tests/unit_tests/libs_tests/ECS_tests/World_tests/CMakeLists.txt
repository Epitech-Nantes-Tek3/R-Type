
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/ECS_tests/World_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/World_class_tests.cpp
)

create_test(
    TEST_NAME World_class_tests
    TEST_SRC ${TEST_SRC_ROOT}
    TEST_DEPS ${PROJECT_NAME}_ecs
)
