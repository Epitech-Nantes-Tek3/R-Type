add_subdirectory(Components)
add_subdirectory(Entity)

set (TARGET ${PROJECT_NAME}_ecs)

add_library(${TARGET}
    ${SRC_COMPONENT}
    ${SRC_ENTITY}
)

set(INCLUDE_ECS_LIB
    ${PROJECT_SOURCE_DIR}/libs/ECS)

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ECS_LIB}
    PRIVATE ${INCLUDE_ECS_LIB}/Entity
    PRIVATE ${INCLUDE_ECS_LIB}/Components
)

#set_target_properties(ECS PROPERTIES LINKER_LANGUAGE CXX)
