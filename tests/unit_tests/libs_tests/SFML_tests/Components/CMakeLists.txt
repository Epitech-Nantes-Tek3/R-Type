set(SRC_COMPONENT_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/libs_tests/SFML_tests/Components)

set(SFML_COMPONENTS_TESTS_SRC
    ${SRC_COMPONENT_ROOT}/AnimationComponent_tests.cpp
    ${SRC_COMPONENT_ROOT}/SelectedComponent_tests.cpp
    ${SRC_COMPONENT_ROOT}/WritableContentComponent_tests.cpp
    PARENT_SCOPE
)
