set(SRC_ROOT ${PROJECT_SOURCE_DIR}/Client)

set(SRC_CLIENT
    ${SRC_ROOT}/main.cpp
    PARENT_SCOPE
)

add_subdirectory(SFML_wrapper)