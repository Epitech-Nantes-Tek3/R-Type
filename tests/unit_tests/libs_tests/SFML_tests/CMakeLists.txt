set(SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/SFML_tests)

add_subdirectory(Systems)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/AllowControllerComponentTests.cpp
    ${SRC_ROOT}/AllowMouseAndKeyboardComponentTests.cpp
    ${SRC_ROOT}/GraphicsRectangleComponentTests.cpp
    ${SRC_ROOT}/GraphicsTextComponentTests.cpp
    ${SFML_SYSTEMS_TESTS_SRC}
)

create_test(
    TEST_NAME SFML_tests
    TEST_SRC ${TEST_SRC_ROOT}
    TEST_DEPS ${PROJECT_NAME}_SFMLGraphicECS
)
