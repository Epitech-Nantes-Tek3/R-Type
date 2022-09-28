add_subdirectory(Components)
add_subdirectory(Entity)
add_subdirectory(World)

set (TARGET ${PROJECT_NAME}_ecs)

add_library(${TARGET}
    ${SRC_COMPONENT}
    ${SRC_ENTITY}
    ${SRC_WORLD}
)

set(INCLUDE_ECS_LIB
    ${PROJECT_SOURCE_DIR}/libs/ECS)

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ECS_LIB}
    PRIVATE ${INCLUDE_ECS_LIB}/Entity
    PRIVATE ${INCLUDE_ECS_LIB}/Components
    PRIVATE ${INCLUDE_ECS_LIB}/Worlds
)

#set_target_properties(ECS PROPERTIES LINKER_LANGUAGE CXX)
