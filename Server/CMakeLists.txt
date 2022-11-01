add_subdirectory(Room)

set(SRC_ROOT ${PROJECT_SOURCE_DIR}/Server)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/Server)

set(TARGET_SERVER r-type_server)

set(SRC_SERVER
    ${SRC_ROOT}/main.cpp
    ${SRC_ROOT}/Server.cpp
    ${INC_ROOT}/Server.hpp
    ${SRC_ROOT}/Room/Room.cpp
    ${INC_ROOT}/Room/Room.hpp
)

add_executable(${TARGET_SERVER} ${SRC_SERVER})

set_target_properties(${TARGET_SERVER}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

target_link_libraries(${TARGET_SERVER}
    ${PROJECT_NAME}_transisthor
    ${PROJECT_NAME}_RTypeLogicServer
    ${PROJECT_NAME}_argumentHandler
)
