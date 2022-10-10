
## Setting Variables ##
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/SFML_tests)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/SFML_tests)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/AllowControllerComponentTests.cpp
    ${SRC_ROOT}/AllowMouseAndKeyboardComponentTests.cpp
    ${SRC_ROOT}/ControllerInputComponentTests.cpp
    ${SRC_ROOT}/MouseInputComponentTests.cpp
    ${SRC_ROOT}/KeyboardInputComponentTests.cpp
)

## Documented Example ##
create_test(
    ## First, the name of the test ##
    TEST_NAME SFML_tests
    ## Second, the sources for the test ##
    TEST_SRC ${TEST_SRC_ROOT}
    ## Last, the depenancies (necessary libraries) ##
    TEST_DEPS ${PROJECT_NAME}_SFMLComponents
    ## In this case none, otherwise add TEST_DEPS ${DEPENDANCY_NAME}
)
