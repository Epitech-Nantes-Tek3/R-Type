
set(SRC_ROOT ${PROJECT_SOURCE_DIR}/AdminPanel)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/AdminPanel)

set(TARGET_ROOM r-type_admin_panel)

set(SRC_ROOM
    ${SRC_ROOT}/main.cpp
    ${SRC_ROOT}/AdminPanel.cpp
    ${INC_ROOT}/AdminPanel.hpp
)

add_executable(${TARGET_ROOM} ${SRC_ROOM})

set_target_properties(${TARGET_ROOM}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

target_link_libraries(${TARGET_ROOM}
    ${PROJECT_NAME}_communicator
    ${PROJECT_NAME}_argumentHandler
)

install(TARGETS ${TARGET} DESTINATION bin)