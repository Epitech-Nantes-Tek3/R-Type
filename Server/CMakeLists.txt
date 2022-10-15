set (TARGET r-type_server)

set(SRC_ROOT ${PROJECT_SOURCE_DIR}/Server)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/Server)

set(SRC
    ${SRC_ROOT}/main.cpp
    ${SRC_ROOT}/Server.cpp
    ${SRC_ROOT}/Room.cpp
    ${SRC_SERVER_SYSTEM}
    ${INC_ROOT}/Server.hpp
    ${INC_ROOT}/Room.hpp
)

add_executable(${TARGET} ${SRC})

set_target_properties(${TARGET}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_transisthor
    ${PROJECT_NAME}_argumentHandler
    ${PROJECT_NAME}_gameSystems
)
