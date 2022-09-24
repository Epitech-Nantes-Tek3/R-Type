add_subdirectory(Components)
add_subdirectory(Entity)

add_library(ecs SHARED
    ${SRC_COMPONENT}
    ${SRC_ENTITY}
    )

target_include_directories(ecs PUBLIC ${SRC_COMPONENT} ${SRC_ENTITY})

set_target_properties(ecs PROPERTIES LINKER_LANGUAGE CXX)
