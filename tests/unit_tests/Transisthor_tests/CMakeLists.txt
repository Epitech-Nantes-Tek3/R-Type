set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/Transisthor_tests)

create_test(
    TEST_NAME transisthor_tests
    TEST_SRC ${SRC_ROOT}/Transisthor_tests.cpp
    TEST_DEPS ${PROJECT_NAME}_transisthor
)