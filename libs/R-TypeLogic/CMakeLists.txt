add_subdirectory(Components)
add_subdirectory(EntityManipulation)
add_subdirectory(SharedResources)
add_subdirectory(Systems)

set(TARGET ${PROJECT_NAME}_rl)

add_library(${TARGET}
    ${SRC_RL_COMPONENTS}
    ${SRC_RL_RESOURCES}
    ${SRC_RL_GLOBAL_SYSTEMS}
)

target_include_directories(${TARGET}
    PRIVATE ${PROJECT_NAME}_ecs
)

target_link_libraries(${TARGET}
    ${PROJECT_NAME}_ecs
)
