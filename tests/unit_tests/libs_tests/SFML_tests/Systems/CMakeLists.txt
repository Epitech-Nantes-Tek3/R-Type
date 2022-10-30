set(SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/SFML_tests/Systems)

set(SFML_SYSTEMS_TESTS_SRC
    ${SRC_ROOT}/InputManagement_tests.cpp
    ${SRC_ROOT}/SoundManagementTests.cpp
    ${SRC_ROOT}/AnimationSystem_tests.cpp
    PARENT_SCOPE
)
