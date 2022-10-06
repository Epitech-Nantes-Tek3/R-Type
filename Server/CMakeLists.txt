set (TARGET r-type_server)

set(SRC_ROOT ${PROJECT_SOURCE_DIR}/Server)
set (INC_ROOT ${PROJECT_SOURCE_DIR}/Server)

set(SRC
    ${SRC_ROOT}/main.cpp
)

add_executable(${TARGET} ${SRC})

set_target_properties(${TARGET}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/
)

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PUBLIC ${PROJECT_NAME}_transisthor
    INTERFACE ${PROJECT_NAME}_error
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_error
    ${PROJECT_NAME}_transisthor
)