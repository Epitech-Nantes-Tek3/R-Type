set(SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/SFML_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/AllowControllerComponentTests.cpp
    ${SRC_ROOT}/AllowMouseAndKeyboardComponentTests.cpp
    ${SRC_ROOT}/GraphicsRectangleComponentTests.cpp
    ${SRC_ROOT}/GraphicsTextComponentTests.cpp
    ${SRC_ROOT}/Input_functions_tests.cpp
)

create_test(
    TEST_NAME SFML_tests
    TEST_SRC ${TEST_SRC_ROOT}
    TEST_DEPS ${PROJECT_NAME}_SFMLComponents
)
