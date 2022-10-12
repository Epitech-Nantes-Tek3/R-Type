add_subdirectory(Both)
add_subdirectory(Client)
add_subdirectory(Server)

set(TARGET ${PROJECT_NAME}_tel)

add_library(${TARGET}
    ${SRC_TEL_BOTH}
    ${SRC_TEL_CLIENT}
    ${SRC_TEL_SERVER}
)

set(INCLUDE_TEL_LIB
    ${PROJECT_SOURCE_DIR}/libs/TransisthorECSLogic)

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_TEL_LIB}
    INTERFACE ${PROJECT_NAME}_ecs
    PRIVATE ${INCLUDE_ECS_LIB}/Entity
    PRIVATE ${INCLUDE_ECS_LIB}/Component
    PRIVATE ${INCLUDE_ECS_LIB}/World
    PRIVATE ${INCLUDE_ECS_LIB}/System
    PRIVATE ${INCLUDE_ECS_LIB}/Resource
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
