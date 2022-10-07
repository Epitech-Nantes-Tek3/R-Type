add_subdirectory(Component)
add_subdirectory(Entity)
add_subdirectory(World)
add_subdirectory(System)
add_subdirectory(Resource)

set(TARGET ${PROJECT_NAME}_ecs)

add_library(${TARGET}
    ${SRC_COMPONENT}
    ${SRC_ENTITY}
    ${SRC_WORLD}
    ${SRC_SYSTEM}
    ${SRC_RESOURCE}
)

set(INCLUDE_ECS_LIB
    ${PROJECT_SOURCE_DIR}/libs/ECS)

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ECS_LIB}
    INTERFACE ${PROJECT_NAME}_error
    PRIVATE ${INCLUDE_ECS_LIB}/Entity
    PRIVATE ${INCLUDE_ECS_LIB}/Component
    PRIVATE ${INCLUDE_ECS_LIB}/World
    PRIVATE ${INCLUDE_ECS_LIB}/System
    PRIVATE ${INCLUDE_ECS_LIB}/Resource
    PRIVATE ${PROJECT_NAME}_transisthor
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_error
    ${PROJECT_NAME}_transisthor
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
